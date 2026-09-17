while [ 1 ]; do
    /usr/bin/time -o out -f '%S,%U,%e' ./abg.out -s 0 --edges 100000 --vertices 10000 >/dev/null 2>&1
    cat out | tee -a benchmarking/render_smart_push_v_10000_e_100000_s_0/out.csv
    sleep 1
done
