
clear all;

powers = 1:5;

n = length(powers);

a = 0;
b = 2.5;

% array of h = [1/2, 1/2^2, 1/2^3, ...]
hs = 2.^(-powers);

f = @(x,y) -1.2*y + 7*exp(-0.3*x);

y_init = 3;

y_true = @(x) (70/9)*exp(-0.3*x) - (43/9)*exp(-1.2*x);

% Euler's explicit method
function [ys] = Euler_explicit(f, a, b, hs, y0)
	for j=1:length(hs)
		h = hs(j);
		x = a:h:b;
		n = length(x);
		y = zeros(1,n);
		y(1) = y0;
		for i=1:(n-1)
			slope = f(x(i),y(i));
			y(i+1) = y(i) + slope*h;
		end
		ys(j) = y(n);
	end
end

% Modified Euler's method
function [ys] = Euler_modified(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
	ys = zeros(1,length(hs));
end

% Midpoint method
function [ys] = midpoint(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
	ys = zeros(1,length(hs));
end

% Heun's 2nd order method
function [ys] = Heun_2nd(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
	ys = zeros(1,length(hs));
end

% 3rd order Runge-Kutta method (classical)
function [ys] = RK3_classical(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
	ys = zeros(1,length(hs));
end

% 3rd order Runge-Kutta method (Nystrom's)
function [ys] = RK3_Nystrom(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
	ys = zeros(1,length(hs));
end

% 4th order Runge-Kutta method (classical)
function [ys] = RK4_classical(f, a, b, hs, y0)
% TODO: Remove the following line and fill in the correct code.
	ys = zeros(1,length(hs));
end


	
function [y] = convert_data(x)
	y = abs(log(x(2:end)./x(1:(end-1)))./log(2));
end
N_methods = 7;

data = zeros(N_methods, n);

data(1,:) = abs(y_true(b) - Euler_explicit(f, a, b, hs, y_init));
data(2,:) = abs(y_true(b) - Euler_modified(f, a, b, hs, y_init));
data(3,:) = abs(y_true(b) - midpoint(f, a, b, hs, y_init));
data(4,:) = abs(y_true(b) - Heun_2nd(f, a, b, hs, y_init));
data(5,:) = abs(y_true(b) - RK3_classical(f, a, b, hs, y_init));
data(6,:) = abs(y_true(b) - RK3_Nystrom(f, a, b, hs, y_init));
data(7,:) = abs(y_true(b) - RK4_classical(f, a, b, hs, y_init));


vec_cols = {'red', 'blue', 'green', 'black', 'cyan', 'magenta', 'yellow'};
vec_names = {'Euler''s explicit (O(h))',
			'Modified Euler''s method (O(h^2))',
			'Midpoint method (O(h^2))',
			'Heun''s 2nd order method (O(h^2))',
			'RK3 (classical) (O(h^3))',
			'RK3 (Nystrom''s) (O(h^3))',
			'RK4 (classical) (O(h^4))'};
vec_xticks = {};
for i=1:n
	vec_xticks{i,1} = sprintf('2^(-%d)', powers(i));
end


% plot (absolute) true error with respect to h
hsteps = 1:n;
figure(1);
clf;
title('(absolute) true error w.r.t. h');
xlim([0,n+2]);
set(gca(), 'xtick', hsteps);
set(gca(), 'xtickLabel', vec_xticks);
hold on;
for i=1:N_methods 
	hold on;
	plot(hsteps, data(i,:), 'Color', vec_cols{i}, 'Marker', '.');
end
hold on;
legend(vec_names{1}, vec_names{2}, vec_names{3}, vec_names{4}, vec_names{5}, vec_names{6},...
		vec_names{7});


% plot the order of truncation error 
hsteps = 1:(n-1);
figure(2);
clf;
title('log of true relative error');
xlim([0,n]);
ylim([0,7]);
set(gca(), 'xtick', hsteps);
set(gca(), 'xtickLabel', {});
for i=1:N_methods
	hold on;
	plot(hsteps, convert_data(data(i,:)), 'Color', vec_cols{i}, 'Marker', '.');
end
hold on;
legend(vec_names{1}, vec_names{2}, vec_names{3}, vec_names{4}, vec_names{5}, vec_names{6},...
	vec_names{7});



