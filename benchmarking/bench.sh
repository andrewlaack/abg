while [ 1 ]; do
    /usr/bin/time -o out -f '%S,%U,%e' ./abg.out -s 0 --edges 2000000 --vertices 200000 >/dev/null 2>&1
    cat out | tee -a benchmarking/final_no_render_v_200000_e_2000000_s_0/out1.csv
    sleep 1
done
