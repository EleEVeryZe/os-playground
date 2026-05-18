#!/bin/bash

curlOnProgram() {
    program=${1:-0}
    listProgram=("SINGLE-THREADED" "MULTI-THREADED" "SELECT-THREADED")
    item="${listProgram[$program]}"
    printf -- "---- Program %s -----\n" "$item"
    
    startTime=$(date +%s%3N)
    
    pids=""
    
    count=1
    while [ $count -le 10 ]; do
        (
            curl -s -o /dev/null "http://localhost:808$program"
            nowIs=$(date +%s%3N)
            printf "Req[%d] na Porta 808%d - Finalizada em: %d.%03d\n" \
            $count $program $((nowIs / 1000)) $((nowIs % 1000))
        ) &
        pids="$pids $!"
        ((count++))
    done
    
    wait $pids
    
    endTime=$(date +%s%3N)
    elapsedMs=$((endTime - startTime))
    printf "Total Time: %d.%03d s\n" $((elapsedMs / 1000)) $((elapsedMs % 1000))
    echo "------------------------"
    
}

make kill > /dev/null 2>&1
make all

printf "[1] - SingThreaded\n[2] - multiThreaded\n[3] - select_thread_server\n[A] - RUN ALL \n";
read option
printf "Selected option: %s\n" $option

if [ "$option" == "3" ]; then
    stdbuf -oL -eL ./exec/select_thread_server 8082 > t2.log 2>&1 &
    sleep 1
    curlOnProgram 2
else
    stdbuf -oL -eL ./exec/SingThreaded 8080 > t0.log 2>&1 &
    stdbuf -oL -eL ./exec/multiThreaded 8081 > t1.log 2>&1 &
    stdbuf -oL -eL ./exec/select_thread_server 8082 > t2.log 2>&1 &
    
    sleep 2
    
    program=0
    while [ $program -lt 3 ]; do
        
        curlOnProgram $program
        ((program++))
    done
    
    make kill > /dev/null 2>&1
fi