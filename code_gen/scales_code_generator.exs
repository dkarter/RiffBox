defmodule ScalesCodeGenerator do
  @moduledoc """
  This is just some quick and dirty music theory based scale generator.

  There's a more modular way to approach this and I may end up extracting the
  logic into a module one day, but for now this serves the purpose of generating
  some static C++ constatnts for use in an Arduino based project.
  """

  @notes ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]

  @scale_formulas %{
    ionian: ["1", "2", "3", "4", "5", "6", "7"],
    dorian: ["1", "2", "b3", "4", "5", "6", "b7"],
    phrygian: ["1", "b2", "b3", "4", "5", "b6", "b7"],
    lydian: ["1", "2", "3", "#4", "5", "6", "7"],
    mixolydian: ["1", "2", "3", "4", "5", "6", "b7"],
    aeolian: ["1", "2", "b3", "4", "5", "b6", "b7"],
    locrian: ["1", "b2", "b3", "4", "b5", "b6", "b7"]
  }

  @interval_mappings %{
    "1" => 0,
    "b2" => 1,
    "2" => 2,
    "b3" => 3,
    "3" => 4,
    "4" => 5,
    "#4" => 6,
    "b5" => 6,
    "5" => 7,
    "#5" => 8,
    "b6" => 8,
    "6" => 9,
    "bb7" => 9,
    "b7" => 10,
    "7" => 11
  }

  @cpp_file_header """
  /* ******************************************
   *  Auto Generated File                     *
   *                                          *
   *  Do not edit manually!                   *
   * ******************************************/

  """

  def run do
    generate_cpp_header_file()

    generate_keys()
    |> generate_cpp_file()
  end

  defp generate_cpp_header_file do
    code = """
    #include <Arduino.h>

    void notesForMode(int key, int mode, String *scaleNotes);
    """

    File.write!("./src/Music.h", [@cpp_file_header, code] |> Enum.join("\n"))
  end

  # faking dictionary access
  defp generate_cpp_file(keys) do
    includes = """
    #include <Arduino.h>
    #include <Music.h>
    #include <string.h>
    """

    constants =
      keys
      |> Enum.map(fn key -> {key, generate_scales_for_key(key)} end)
      |> Enum.map(&key_modes_to_cpp/1)
      |> List.flatten()
      |> Enum.join("\n")

    function_start = """
    \n
    void copyNotes(String *from, String *to) {
      for (int i; i < 7; i++) {
        to[i] = from[i];
      }
    }

    void notesForMode(int key, int mode, String *scaleNotes) {
      String selector = String(String(key) + "," + String(mode));
    """

    modes = Map.keys(@scale_formulas)

    cases =
      for key <- keys, mode <- modes do
        var_name = cpp_scale_var_name(key, mode)
        key_index = Enum.find_index(keys, &(&1 == key))
        mode_index = Enum.find_index(modes, &(&1 == mode))

        """
            if (key == #{key_index} && mode == #{mode_index}) {
              copyNotes(#{var_name}, scaleNotes);
              return;
            }
        """
      end

    function_end = """
    }
    """

    code =
      [
        @cpp_file_header,
        includes,
        constants,
        function_start,
        cases,
        function_end
      ]
      |> Enum.join("\n")

    File.write!("./src/Music.cpp", code, [])
  end

  defp key_modes_to_cpp({key, modes}) do
    modes
    |> Enum.map(fn {mode_name, notes} ->
      size = length(notes)
      notes = notes |> Enum.map(fn n -> "\"#{n}\"" end) |> Enum.join(", ")
      var_name = cpp_scale_var_name(key, mode_name)
      "String #{var_name}[#{size}] = {#{notes}};"
    end)
  end

  defp cpp_scale_var_name(key, mode) do
    note_name =
      key
      |> String.split("")
      |> Enum.map(fn
        "#" -> "Sharp"
        "b" -> "Flat"
        note -> String.downcase(note)
      end)

    mode_name = mode |> Atom.to_string() |> String.capitalize()
    "#{note_name}#{mode_name}"
  end

  defp generate_keys do
    @notes
    |> Enum.reduce([], fn next_note, acc ->
      case List.last(acc) do
        prev_note when is_binary(prev_note) ->
          # if we find a sharp note in the previous, add the current note and
          # inverted accidental
          if accidental?(prev_note) do
            inverted_accidental = invert_accidental(prev_note)
            acc ++ [inverted_accidental, next_note]
          else
            acc ++ [next_note]
          end

        # no prev note found (list was empty because this is the first one we
        # are trying)
        nil ->
          # return the first note
          [next_note]
      end
    end)
  end

  defp generate_scales_for_key(key) do
    @scale_formulas
    |> Enum.map(&generate_scale(&1, key))
    |> Enum.into(%{})
  end

  defp generate_scale({scale_name, formula}, key) do
    # instead of including both flat and sharp notes in the note list which will
    # make things difficult, if we have a flat key we just create the scale for
    # the inverted accidental and then invert each of the resulting notes
    if flat?(key) do
      inverted_key = invert_accidental(key)

      notes =
        formula
        |> formula_to_notes(inverted_key)
        |> Enum.map(fn note ->
          if accidental?(note), do: invert_accidental(note), else: note
        end)

      {scale_name, notes}
    else
      {scale_name, formula_to_notes(formula, key)}
    end
  end

  defp formula_to_notes(formula, key) do
    key_index = note_index(key)

    Enum.map(formula, fn interval ->
      interval_value = Map.get(@interval_mappings, interval)
      virtual_index = key_index + interval_value
      note_at_virtual_index(virtual_index)
    end)
    |> humanize_scale_notes()
  end

  # converts a scale with non-sensical notes e.g.:
  # C Minor: [C, D, D#, F, G, G#, A#] -> [C, D, Eb, F, G, Ab, Bb]
  defp humanize_scale_notes(scale_notes) do
    scale_notes
    |> Enum.reduce([], fn next_note, acc ->
      case List.last(acc) do
        prev_note when is_binary(prev_note) ->
          next_note = humanize_scale_note(prev_note, next_note)
          acc ++ [next_note]

        # no prev note found (list was empty because this is the first one we
        # are trying)
        nil ->
          # return the first note
          [next_note]
      end
    end)
  end

  # compare first letter of each note (e.g. A and A# -> A == A)
  # in that case we want to replace A# with Bb to make it a more "human"
  # scale
  defp humanize_scale_note(prev_note, next_note) do
    if String.slice(prev_note, 0, 1) == String.slice(next_note, 0, 1) do
      invert_accidental(next_note)
    else
      next_note
    end
  end

  defp invert_accidental(note) do
    cond do
      String.match?(note, ~r/[A-G]#/) ->
        virtual_index = note_index(note) + 1
        new_note = note_at_virtual_index(virtual_index)

        "#{new_note}b"

      String.match?(note, ~r/[A-G]b/) ->
        base_note = String.slice(note, 0, 1)
        virtual_index = note_index(base_note) - 1

        note_at_virtual_index(virtual_index)

      true ->
        note
    end
  end

  defp note_index(key) do
    Enum.find_index(@notes, fn note -> note == key end)
  end

  defp note_at_virtual_index(virtual_index) do
    wrapped_index = calculate_wrapped_note_index(virtual_index)
    Enum.at(@notes, wrapped_index)
  end

  # calculates the "virtual" index, allowing for cycles around the note array in
  # case we are starting from the middle of the list
  defp calculate_wrapped_note_index(virtual_index) do
    note_count = length(@notes)
    whole_cycles = floor(virtual_index / note_count)

    if virtual_index >= note_count do
      virtual_index - whole_cycles * note_count
    else
      virtual_index
    end
  end

  defp sharp?(note), do: String.match?(note, ~r/[A-Z]#/)
  defp flat?(note), do: String.match?(note, ~r/[A-Z]b/)
  defp accidental?(note), do: sharp?(note) || flat?(note)
end

ScalesCodeGenerator.run()
|> IO.inspect()
