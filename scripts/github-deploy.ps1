param(
  [Parameter(Mandatory=$true)]
  [string]$rtoken,
  [Parameter(Mandatory=$true)]
  [string]$cid,
  [Parameter(Mandatory=$true)]
  [string]$projectId,
  [Parameter(Mandatory=$true)]
  [string]$wd
)

Write-Host "Changing directory to: $wd"
Set-Location $wd

Write-Host "Install beam-cli ..."
dotnet tool restore
Write-Host "Done installing beam-cli"

$timeoutSeconds = 30
Write-Host "Initiating beam init ..."
$process = Start-Process -FilePath "dotnet" -ArgumentList "beam login --save-to-file --refresh-token $rtoken --cid $cid --pid $projectId" -NoNewWindow -PassThru
$process | Wait-Process -Timeout $timeoutSeconds

if (!$process.HasExited) {    
    $process.Kill()
    Write-Output "Login failed. Exiting script.."
} else {
    Write-Host "Start deployment ..."
	dotnet beam deploy plan
    dotnet beam deploy release --latest-plan -q
}