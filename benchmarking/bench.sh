while [ 1 ]; do
    /usr/bin/time -o out -f '%S,%U,%e' ./abg.out -s 0 --edges 1000000 --vertices 100000 >/dev/null 2>&1
    cat out | tee -a benchmarking/no_render_v_100000_e_1000000_s_0/out1.csv
    sleep 1
done
