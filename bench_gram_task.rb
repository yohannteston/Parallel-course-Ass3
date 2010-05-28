#!/usr/local/bin/ruby

# Benchmark for gram2
# For each size and each number of thread launch 20 times
# the program and keep the least time.

[2000, 3000].each_with_index do |size, i|
	if (i > 0)
		puts "\n\n";
	end
	puts "# #{size}"

	min_ref=0 ;

	[1,4,8,12,16,24,32,48,64].each_with_index do |n,j|
		min_time = 10000000000 ;

		ENV['OMP_NUM_THREADS'] = "#{n}" ;
		5.times {
			out = `./gram_schmidt_task #{size} #{size}` 
			out_split = out.split " " ;
			if(out_split[1].to_f < min_time)
				min_time = out_split[1].to_f;
			end
		}

		if ( j == 0)
			min_ref = min_time ;
		end

		puts "#{size}  #{n}  #{min_ref}  #{min_time}" ;
	end
end
