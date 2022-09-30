Param(
    [Parameter(Mandatory = $false, Position = 1, HelpMessage = "Lab or test number")] 
    [int]
    $lab = -1,
    [Parameter(Mandatory = $false, Position = 2, HelpMessage = "Is assignment a test")]
    [bool]
    $isTest = $false
)

$json_path = "./data.json"

if (!(Test-Path -Path $json_path)) {
    Write-Host "`e[37;41mdata.json does not exist!`e[0m"
    exit
}

function Validate-Value {
    Param(
        [Parameter(Position = 1)]
        [string]
        $key
    )

    if (!$values[$key]) {
        Write-Host "`e[37;41mKey $key does not exist!`e[0m"
        exit
    }
}

$values = Get-Content -Raw $json_path | ConvertFrom-Json -AsHashtable

$keys = @(
    "semester",
    "variant",
    "lab",
    "group",
    "student",
    "teacher"
)

foreach ($key in $keys) {
    if (!$values.ContainsKey($key)) {
        Write-Host "`e[37;41mKey $key does not exist!`e[0m"
        exit
    }
}

if ($lab -gt 0) {
    $values["lab"] = $lab
}
else {
    $values["lab"] = $values["lab"] + 1;
}

$null = Remove-item $json_path
ConvertTo-Json $values | Out-File $json_path -Force

$label = $isTest ? "Test" : "Lab";
$lab_dir = "./Semester-$($values["semester"])/$label-work-$($values["lab"])";
$word_dir = "$lab_dir/docs/Report-Variant-$($values["variant"]).docx"

if (Test-Path -Path $lab_dir) {
    Write-Host "`e[37;41m Directory already exists!`e[0m"
    exit
}

$null = mkdir $lab_dir;
Write-Host "`e[32mCreated `e[0m$lab_dir"

$null = mkdir "$lab_dir/docs/graphs";
Write-Host "`e[32mCreated `e[0m$lab_dir/docs/graphs"

$null = mkdir "$lab_dir/docs/examples";
Write-Host "`e[32mCreated `e[0m$lab_dir/docs/examples"

$null = mkdir "$lab_dir/src";
Write-Host "`e[32mCreated `e[0m$lab_dir/src"

$null = Copy-Item "./templates/src/*" "$lab_dir/src/" -Recurse;
Write-Host "`e[33mCopied `e[0m ./templates/src/* `e[33mto`e[0m $lab_dir/src"
$null = Copy-Item "./templates/Makefile" "$lab_dir/Makefile";
Write-Host "`e[33mCopied `e[0m ./templates/documents-$($label.ToLower())/report.docx `e[33mto`e[0m $word_dir"
$null = Copy-Item "./templates/documents-$($label.ToLower())/report.docx" $word_dir

$Word = New-Object -ComObject Word.Application
$file = Get-Item $word_dir
$Document = $Word.Documents.Open($file.FullName)

$MatchCase = $true
$MatchWholeWorld = $false
$MatchWildcards = $false
$MatchSoundsLike = $false
$MatchAllWordForms = $false
$Forward = $false
$Wrap = 1
$Format = $false
$Replace = 2

foreach ($value in $values.GetEnumerator()) {
    $null = $Document.Content.Find.Execute($value.Name.ToString().ToUpper(), $MatchCase, $MatchWholeWorld, $MatchWildcards, $MatchSoundsLike, $MatchAllWordForms, $Forward, $Wrap, $Format, $value.Value, $Replace)
}

Write-Host "`e[34mUpdated`e[0m $word_dir";

$Document.Close(-1)
$Word.Quit()