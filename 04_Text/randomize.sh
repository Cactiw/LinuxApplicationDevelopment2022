#!/bin/bash

SLEEP_DELAY=${1:-0.1}
x=0
y=0
data=()

while IFS= read -r line
do
  while IFS='' read -r -d '' -n 1 char; do
    data+=("$x.$y.$char")
    ((x++))
  done < <(printf %s "$line")
  x=0
  ((y++))
done

last_line=y
tput clear
data_shuffled="$(echo "${data[@]}" | xargs -n1 | sort -R)"

while IFS='.' read -r cur_x cur_y char
do
  tput cup "$cur_y" "$cur_x"
  echo -n "$char"
  if [[ ${char: -1} != $'\r' ]] && [[ $char != $' ' ]]; then
    # shellcheck disable=SC2086
    sleep $SLEEP_DELAY
    fi

done <<< "$data_shuffled"
tput cup $last_line 0
