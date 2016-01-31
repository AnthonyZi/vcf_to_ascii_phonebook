echo "combined vcf:" > combine.vcf
for file in vcfs/*
do
        cat "$file" >> combine.vcf
done
