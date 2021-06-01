#!/usr/bin/env bash
echo "prog2 [space count]: $(tr -d -c '{[:space:]}' | wc -c)"

