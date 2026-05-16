#!/bin/bash

# ---------- CONFIG ----------
CMD="./codexion 199 2100 100 100 100 10 600 edf"
# ----------------------------

total_runs=0
successful_runs=0

declare -A burnout_count

echo "Starting stress test..."
echo "Command: $CMD"
echo

while true
do
    ((total_runs++))

    output=$($CMD)

    burned_line=$(echo "$output" | grep "burned out")

    if [ -n "$burned_line" ]; then
    {
        timestamp=$(date "+%H:%M:%S")

        coder=$(echo "$burned_line" | awk '{print $2}')

        ((burnout_count[$coder]++))

        echo "[$timestamp] RUN #$total_runs"
        echo "$burned_line"
        echo

        echo "------ STATS ------"
        echo "Successful runs : $successful_runs"
        echo "Total runs      : $total_runs"
        echo

        echo "Burnout frequency:"
        for id in "${!burnout_count[@]}"
        do
            echo "Coder $id -> ${burnout_count[$id]}"
        done

        echo "-------------------"
        echo
    }
    else
    {
        ((successful_runs++))
        echo "Run #$total_runs completed successfully"
    }
    fi
done
