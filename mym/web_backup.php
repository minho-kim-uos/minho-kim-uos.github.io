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

<? include "../.htuserinfo.php" ; ?>

<?
$exclude1 = "logs";
$exclude2 = "mym";
$exclude3 = "$account"."_*.tgz";

$date = date('Ymd.His');
echo "<html><head><meta HTTP-EQUIV=Content-Type CONTENT=text/html; charset=Korean><title>�������</title></head>\n\n";
echo "<body bgcolor=#DDE2E9>\n\n";

echo "<font size=2px>* �Ϸ�޼����� ���ö����� ����Ͽ� �ֽʽÿ� <br><br>"; 
echo "* ����������� : $exclude1 <br>\n\n";
echo "* ����������� : $exclude2 <br>\n\n";
echo "* ����������� : $exclude3 <br>\n\n";
echo "* �����...........<br><br>\n\n";
flush();

$backup_command = "cd $rootdir && tar cvzfp mym/$account"."_$date.tgz ./ --exclude $exclude1 --exclude $exclude2 --exclude $exclude3 1>/dev/null"; 
system($backup_command); 
system("chmod 707 $rootdir"."mym/"."$account"."_$date.tgz"); 
echo ">> ����� <font color=blue>�Ϸ�</font> �Ǿ����ϴ�.<br>\n\n"; 
echo "������� : <font color=blue>";
system("du -h $rootdir"."mym/"."$account"."_$date.tgz");

echo "</font><br><br>";
echo "��� ���� ������ <font color=red>FTP</font> �� ������ �����Ͽ�, <font color=red>�ٿ�ε�</font> ������ �� �ֽ��ϴ�.<br>\n\n";
echo "��� ������ �ٿ�ε��� ���� <font color=red>����</font>�� �Ͽ� �ֽñ� �ٶ��ϴ�. </font><br>\n\n";
echo "<br><br>\n\n";
echo "<div align=center><input type=button value=â�ݱ� onClick ='self.close ()'></div>\n\n";
echo "</body></html>\n\n"

?>
