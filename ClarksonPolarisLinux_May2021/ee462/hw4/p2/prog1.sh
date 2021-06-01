#!/usr/bin/env bash
tail -n +6 | tr '{[:lower:], [:upper:]}' '{[:upper:], [:lower:]}'


