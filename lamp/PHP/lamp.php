<?php
$status = exec("sudo gpioctrl status 15");
if($_GET['action'] == "toggle")
{
    if($status == "on")
    {
        $cmd = "sudo gpioctrl off 15";
    }
    else
    {
        $cmd = "sudo gpioctrl on 15";
    }
    $status = exec($cmd);
    $result = [
                "code" => 200,
                "status" => $status,
              ];
    header('Content-type:application/json');
    echo json_encode($result, true);
    exit();
}
?>
<!DOCTYPE html>
<html>
    <head>
        <title>Y!an's lamp</title>
        <style>
            .center{  
                margin: auto;
                position: absolute;
                top: 0; left: 0; bottom: 0; right: 0;
                }
            .on{
                background-color: #FCFCFC;
            }
            .off{
                background-color: #0C0C0C;
            }
        </style>  
    </head>
    <body class="<?php echo $status ?>" >
        <a href="javascript:"><img id="switch" src="lamp_<?php echo $status ?>.png" class="center"></a>
        <script src="jquery-2.2.3.min.js"></script>
        <script type="text/javascript">
            $("#switch").click(function(){
                $.ajax({
                    url: "lamp.php?action=toggle",
                    success: function(data){
                        if(data.status == "off")
                        {
                            $("body").removeClass().addClass("off");
                            $("#switch").attr('src','lamp_off.png');
                        }
                        else if(data.status == "on")
                        {
                            $("body").removeClass().addClass("on");
                            $("#switch").attr('src','lamp_on.png');
                        }
                    },
                    });
            })
        </script>
    </body>
</html>