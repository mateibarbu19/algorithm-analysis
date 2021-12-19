make clean
make build

INPUT_DIR=other_tests
OUTPUT_DIR=other_out
#INPUT_DIR=in
OUT

rm -f $OUTPUT_DIR/times_disjoint-set.txt 2> /dev/null
rm -f $OUTPUT_DIR/times_rmq.txt 2> /dev/null

echo
echo "===== RUN LCA_DISJOINT-SET ====="
echo "Test folder: $INPUT_DIR"

for i in {0..5}; do
    (time -p ./lca_disjoint-set $INPUT_DIR/test$i.in $OUTPUT_DIR/test$i.out) 2> time.txt
    cat time.txt | head -n 1 | cut -d' ' -f2 >> $OUTPUT_DIR/times_disjoint-set.txt
done

echo
echo "===== RUN LCA_RMQ ====="
echo "Test folder: $INPUT_DIR"

for i in {0..5}; do
    (time -p ./lca_rmq $INPUT_DIR/test$i.in $OUTPUT_DIR/test$i.out) 2> time.txt
    cat time.txt | head -n 1 | cut -d' ' -f2 >> $OUTPUT_DIR/times_rmq.txt
done

make clean
rm -f time.txt
