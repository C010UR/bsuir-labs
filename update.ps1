$pregSemester = "Semester-\d+"
$pregLab = "(Lab-work-\d+)|(Test-work-\d+)"

$src = Get-ChildItem "./templates/src/*/*"
$makefile = Get-Item ./templates/Makefile

$semesters = Get-ChildItem . -Directory | Where-Object -FilterScript { $_.Name -match $pregSemester }

foreach ($semester in $semesters) {
    $folders += Get-ChildItem $semester -Directory | Where-Object -FilterScript { $_.Name -match $pregLab }
}

foreach ($folder in $folders) {
    Write-Host "`e[34m$($folder.Name)`e[0m:";
    foreach ($file in $src) {
        $path = "$($folder.FullName)/src/$(Split-Path(Split-Path $file -Parent) -Leaf)/$($file.Name)"
        if (Get-Item $path -ErrorAction SilentlyContinue) {
            Remove-Item $path
            Copy-Item $file.FullName $path
            Write-Host "  `e[33m: `e[0m $path"
        }
        else {
            Copy-Item $file.FullName $path
            Write-Host "  `e[32m+ `e[0m $path"
        }
    }
    $path = "$($folder.FullName)/Makefile"
    if (Get-Item $path -ErrorAction SilentlyContinue) {
        Remove-Item $path
        Copy-Item $makefile.FullName $path
        Write-Host "  `e[33m: `e[0m $path"
    }
    else {
        Copy-Item $makefile.FullName $path
        Write-Host "  `e[32m+ `e[0m $path"
    }
    Write-Host
}