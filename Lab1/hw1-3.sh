#!/bin/bash

# Read parent pid, child pid
path_flag=false
while [ "$#" -gt 0 ]; do
  case "$1" in
    --parent)
      parent="$2"
      shift 2
      ;;
    --child)
      child="$2"
      shift 2
      ;;
    --path)
      path_flag=true
      shift
      ;;
    *)
      echo "Unknown parameter passed: $1"
      exit 1
      ;;
  esac
done

# Check if parent or child is empty
if [ -z "$parent" ] || [ -z "$child" ]; then
  echo "Usage: $0 --parent PARENT_PID --child CHILD_PID [--path]"
  exit 1
fi

########
# TODO #
########

path="$child"
temp_pid="$child"

while [ "$temp_pid" != 0 ]; do
  if [ "$temp_pid" -eq "$parent" ]; then
    echo "Yes"
    if [ "$path_flag" = true ]; then
      echo "$path"
    fi
    exit 0
  fi
  temp_pid=$(ps -o ppid= -p "$temp_pid" | tr -d ' ')
  path="$temp_pid -> $path"
done
echo "No"