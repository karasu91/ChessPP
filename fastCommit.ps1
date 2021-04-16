$newGuid = [guid]::NewGuid().tostring().split("-")[0]
git add .
git commit -m "fastCommit id $newGuid"
git push origin main