function [ out ] = plotModelElData( filePath )
%plotModelElData Used to plot arbitrary time series data from ModelEl runs.
% Data should come in the form of a CSV with parameter names at the top of
% each column.

[A] = importdata(filePath);
disp(A);

figure;
for i = 2: length(A.data),
    plot(A.data(:, 1), A.data(:, 2));
    hold on
end

hold off
legend(A.colheaders(2:end));
title('ModelEl Run');
xlabel('Time (msec)');

out = 1;

end

