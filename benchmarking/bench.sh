while [ 1 ]; do
    /usr/bin/time -o out -f '%S,%U,%e' ./abg.out -s 0 --edges 100000 --vertices 10000 >/dev/null 2>&1
    cat out | tee -a benchmarking/track_to_render_v_10000_e_100000_s_0/out1.csv
    sleep 1
done
