$newGuid = [guid]::NewGuid().tostring().split("-")
$newGuid
git add .
git commit -m "$newGuid"
git push origin main