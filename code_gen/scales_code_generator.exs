defmodule ScalesCodeGenerator do
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

  def run do
    generate_keys()
    |> Enum.map(fn key ->
      {key, generate_scales_for_key(key)}
    end)
    |> Enum.into(%{})
  end

  def generate_keys do
    @notes
    |> Enum.reduce([], fn next_note, acc ->
      case List.last(acc) do
        prev_note when is_binary(prev_note) ->
          # if we find a sharp note in the previous, add the current note and
          # inverted accidental
          if accidental?(prev_note) do
            inverted_accidental = invert_accidental(prev_note)
            acc ++ [next_note, inverted_accidental]
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
      # there's a bug here somewhere with the first number
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
