$newGuid = [guid]::NewGuid().tostring().split("-")[0]
git add .
git commit -m "FastCommit ID=$newGuid"
git push origin main