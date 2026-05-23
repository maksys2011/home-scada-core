#!/bin/bash

cd "$(dirname "$0")"

source venv/bin/activate

python split_sim_server.py
