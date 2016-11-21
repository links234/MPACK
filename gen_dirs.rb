a = Dir[File.join(".", "**", "*.cpp")].map do | x |     
    (x.split('/')[0...-1]).join('/')[2..-1]
end

b = Dir[File.join(".", "**", "*.hpp")].map do | x |
    (x.split('/')[0...-1]).join('/')[2..-1]
end

a += b
#puts a.uniq
f = File.open("dirs.txt", "w")
a.uniq.each { |x| f.write("./" + x.to_s + "\n") }

