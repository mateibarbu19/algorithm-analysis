function generate_test_d(fileName, N, M)
    fileID = fopen(fileName,'w');
    fprintf(fileID, "%u %u\n", N, M);

    for i = 2:N
        t = floor(1 + rand() * (i - 2));
        fprintf(fileID, "%u\n", t);
    endfor

    for i = 1:M
        x = floor(1 + rand() * (N - 1));
        y = floor(1 + rand() * (N - 1));
        fprintf(fileID, "%u %u\n", x, y);
    endfor

    fclose(fileID);
endfunction
