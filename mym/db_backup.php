<?       $configfile = shell_exec(" ls ../.htuserinfo.php ");
         if(!$configfile){
         print "<script>window.alert('ȯ�������� ���ų� ���� �Ǿ����ϴ�. �����ڿ��� �����ϼ���.');history.go(-1)</script>";
         }
?>
<?       $configfile1 = shell_exec(" ls ./.htaccess ");
         if(!$configfile1){
         print "<script>window.alert('�޴��� ���� ������ �������� �ʾ�, ó���� �����˴ϴ�..');history.go(-1)</script>";
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

                        $Alert=$Alert."<script>window.alert('������ mym ������ �۹̼��� 707 �� ������ �̿� �ٶ��ϴ�.');history.go(-1)</script>";
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
                        window.alert('�н����带 �Է��� �ּ���.')
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
                        window.alert('����� �Ϸ�Ǿ����ϴ�. ')
                        history.go(-1)
                        </script>
                        ";
		}else{	
			exec("rm -rf $rootdir"."mym/"."$dbuser"."_$(date +%Y%m%d).sql");
			echo "
			<script>
			window.alert('��� ��й�ȣ�� Ʋ�Ƚ��ϴ�. ')
			history.go(-1)
			</script>
			";
                }
        
}

?>
