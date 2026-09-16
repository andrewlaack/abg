while [ 1 ]; do
    /usr/bin/time -o out -f '%S,%U,%e' ./abg.out -s 0 --edges 10000 --vertices 1000 >/dev/null 2>&1
    cat out | tee -a benchmarking/fg_render_v_1000_e_10000_s_0/out.csv
    sleep 10
done
