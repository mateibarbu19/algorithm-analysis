data_dis = dlmread('../other_out/times_disjoint-set.txt', ' ', 0, 0);
data_rmq = dlmread('../other_out/times_rmq.txt', ' ', 0, 0);

title('Timpul de execuție');
xlabel('Numărul testului');
hold on;
plot([0:length(data_dis)-1], data_dis);
hold on;
plot([0:length(data_rmq)-1], data_rmq);
hold on;
legend('Alg. Tarjan', 'Alg. E.M.I.');
print -color -depsc times.eps
