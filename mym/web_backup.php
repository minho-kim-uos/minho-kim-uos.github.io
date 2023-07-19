<?       $configfile = shell_exec(" ls ../.htuserinfo.php ");
         if(!$configfile){
         print "<script>window.alert('환경파일이 없거나 삭제 되었습니다. 관리자에게 문의하세요.');history.go(-1)</script>";
         }
?>
<?       $configfile1 = shell_exec(" ls ./.htaccess ");
         if(!$configfile1){
         print "<script>window.alert('메니져 접근 인증이 설정되지 않아, 처리가 보류됩니다..');history.go(-1)</script>";
         }
?>


<?

function PermitionCheck($PermitionCheckList,$Permition){

        $i=0;
        $PermitionCheckListSize=sizeof($PermitionCheckList);
        $PermitionSize=sizeof($Permition);

        if($PermitionCheckListSize!=$PermitionSize){

                print "The other array size.";

        }else{

                for($i;$PermitionCheckListSize>$i;++$i){


                        $Dir=shell_exec("dir -dl ".$PermitionCheckList[$i]);
                        $ExplodeDir=explode(" ",$Dir);
                        if($ExplodeDir[0]!=$Permition[$i]){

                        $Alert=$Alert."<script>window.alert('계정내 mym 폴더의 퍼미션을 707 로 조정후 이용 바랍니다.');history.go(-1)</script>";
                        print $Alert;
                        }
                }
        }
}


$PermitionCheckList=Array("./");
$Permition=Array("drwx---rwx");

$Alert=PermitionCheck($PermitionCheckList,$Permition);

?>

<? include "../.htuserinfo.php" ; ?>

<?
$exclude1 = "logs";
$exclude2 = "mym";
$exclude3 = "$account"."_*.tgz";

$date = date('Ymd.His');
echo "<html><head><meta HTTP-EQUIV=Content-Type CONTENT=text/html; charset=Korean><title>계정백업</title></head>\n\n";
echo "<body bgcolor=#DDE2E9>\n\n";

echo "<font size=2px>* 완료메세지가 나올때까지 대기하여 주십시요 <br><br>"; 
echo "* 백업제외폴더 : $exclude1 <br>\n\n";
echo "* 백업제외폴더 : $exclude2 <br>\n\n";
echo "* 백업제외파일 : $exclude3 <br>\n\n";
echo "* 백업중...........<br><br>\n\n";
flush();

$backup_command = "cd $rootdir && tar cvzfp mym/$account"."_$date.tgz ./ --exclude $exclude1 --exclude $exclude2 --exclude $exclude3 1>/dev/null"; 
system($backup_command); 
system("chmod 707 $rootdir"."mym/"."$account"."_$date.tgz"); 
echo ">> 백업이 <font color=blue>완료</font> 되었습니다.<br>\n\n"; 
echo "백업파일 : <font color=blue>";
system("du -h $rootdir"."mym/"."$account"."_$date.tgz");

echo "</font><br><br>";
echo "백업 파일 파일을 <font color=red>FTP</font> 로 계정에 접속하여, <font color=red>다운로드</font> 받으실 수 있습니다.<br>\n\n";
echo "백업 파일은 다운로드후 필히 <font color=red>삭제</font>를 하여 주시기 바랍니다. </font><br>\n\n";
echo "<br><br>\n\n";
echo "<div align=center><input type=button value=창닫기 onClick ='self.close ()'></div>\n\n";
echo "</body></html>\n\n"

?>
