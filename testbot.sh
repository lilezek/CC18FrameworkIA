#!/usr/bin/env bash

sh bot/bot.sh build

ants/linux/playgame.py -So --player_seed $RANDOM --end_wait=0.5 --verbose --log_dir game_logs --turns 1000 --map_file ants/linux/maps/random_walk/random_walk_p02_19.map "$@" \
	"sh bot/bot.sh exec " \
	"python ants/linux/sample_bots/python/HunterBot.py" \
  | # test
java -jar ants/linux/visualizer.jar
