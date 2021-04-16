$newGuid = [guid]::NewGuid()
git add .
git commit -m "$newGuid"
git push origin main