#!/bin/bash

export file=numbers

while [ 1 ]; do
  if [ -f "$file" ]; then
    # File exists

    if ! ln "$file" ".lockfile"
    then
      # Wait until lock is removed (if it is present)
      sleep 1
    else
      # Create lock file
      ln "$file" ".lockfile"

      last_number=$(awk 'END {print $NF}' "$file")
      (( next_number = $last_number + 1 ))
      echo "$next_number" >> "$file"
      echo "Appending $next_number"

      # Release lock
      rm ".lockfile"
    fi
  else
    # No file - create the new one
    echo "1" > "$file"
  fi
done

