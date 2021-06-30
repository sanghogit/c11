git init 
git add c11.cc rvalue.cc regex.cc .gitignore
git commit -m "add .gitignore README.md c11.cc rvalue.cc regex.cc"
git branch -M main 
git remote set-url origin git+ssh://git@github.com/sanghogit/c11.git
git remote add origin
git push -u origin main
