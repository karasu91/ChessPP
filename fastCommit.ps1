$newGuid = [guid]::NewGuid().tostring().split("-")[0]
git add .
git commit -m "fast commit, id=$newGuid"
git push origin main