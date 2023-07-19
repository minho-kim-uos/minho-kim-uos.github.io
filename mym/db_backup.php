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

<? include "../.htuserinfo.php"; ?>
<?
if(!$dbpasswd){
        echo "
                        <script>
                        window.alert('패스워드를 입력해 주세요.')
                        history.go(-1)
                        </script>
                        ";
        exit;
}else{
                $passwd=trim($passwd);
		$cmd = "/usr/bin/mysqldump -u$dbuser -p\"$dbpasswd\" $dbname > $rootdir"."mym/"."$dbuser"."_$(date +%Y%m%d).sql ";
		exec($cmd);
		$filecheck = "/usr/bin/du $rootdir"."mym/"."$dbuser"."_$(date +%Y%m%d).sql|awk '{print $1}'";
		$pp = popen($filecheck, 'r');
		    while (!feof($pp)) {
		        $result .= fgets($pp, 512);
		    }
		pclose($pp);

                if($result > 0){
			exec("chmod 707 $rootdir"."mym/"."$dbuser"."_$(date +%Y%m%d).sql");
		        echo "
                        <script>
                        window.alert('백업이 완료되었습니다. ')
                        history.go(-1)
                        </script>
                        ";
		}else{	
			exec("rm -rf $rootdir"."mym/"."$dbuser"."_$(date +%Y%m%d).sql");
			echo "
			<script>
			window.alert('디비 비밀번호가 틀렸습니다. ')
			history.go(-1)
			</script>
			";
                }
        
}

?>
