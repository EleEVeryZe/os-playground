#!/bin/bash

program=0
listProgram=("SINGLE-THREADED:", "MULTI-THREADED");

while [ $program -lt 2 ]; do
    echo ${listProgram[program]}
    startTime=$(date +%s%3N)
    count=1
    while [ $count -lt 10 ]; do
        (
            curl -s -o /dev/null http://localhost:808$program
            nowIs=$(date +%s%3N)
            
            printf "Time[%d][%d]: %d.%03d\n" $count $program $((nowIs / 1000)) $((nowIs % 1000))
            
        ) &
        
        ((count++))
    done
    
    wait
    
    endTime=$(date +%s%3N)
    elapsedMs=$((endTime - startTime))
    elapsedFinal=$(printf "%d.%03d" $((elapsedMs / 1000)) $((elapsedMs % 1000)))
    
    echo "------------------------"
    echo "Total Time: $elapsedFinal s"
    ((program++))
done

