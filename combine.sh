echo "combined vcf:" > combine.vcf
if [ -d vcfs ]
then
        for file in vcfs/*
        do
         cat "$file" >> combine.vcf
        done
else
        echo "folder vcfs does not exist!"
fi
