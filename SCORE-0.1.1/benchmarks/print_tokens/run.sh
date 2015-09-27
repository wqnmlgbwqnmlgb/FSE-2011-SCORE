#!/bin/bash
if test -z "$1"
then
    echo "Usage: ./run.sh SERVER_IP SERVER_PORT"
    exit 1;
fi
if test -z "$2"
then
    echo "Usage: ./run.sh SERVER_IP SERVER_PORT"
    exit 1;
fi
SCORE_DIR=`dirname $0`/../..
export LD_LIBRARY_PATH=$SCORE_DIR/lib:$LD_LIBRARY_PATH
$SCORE_DIR/bin/score_client -i 1000000000 -t './print_tokens &> /dev/null' -a "$1" -p "$2"
