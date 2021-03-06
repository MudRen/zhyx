#include <ansi.h>
#include <command.h>
#include <net/daemons.h>
#include <net/macros.h>

int LAST_HARD_DIS= 0;
void init_cron();
void autosave();
void check_dns();
void check_pets();
void check_whonature();
void create()
{
        seteuid( ROOT_UID );
        init_cron();
}
int query_last_hard_dis()
{
        return LAST_HARD_DIS;
}
int set_last_hard_dis()
{
        LAST_HARD_DIS = time();
        return time();
}
void init_cron()
{
        mixed *local;
        local = localtime(time());
// every 45 mins, autosave every player
        if ( !((local[1])%55)) autosave();
// On average tasks get renewed every 30 mins
        if ( !random(16))
      TASK_D->init_dynamic_quest();


//How long the system will refresh all tasks. Added by FY@SH-Morrison
//--------------------------------------------------------------------
 if ( !((local[1])%5))
     {
        message("system", HIY "\n【系统消息】:"+BLINK HIR+" 系统将在五分钟后重新分配使命。\n"NOR,users());
        call_out("countdown", 20, 5);
}

//--------------------------------------------------------------------
//修改以上第一行中百分号后的数字(现在设的60代表1小时)就可以修改task重新分布的时间间间隔了。
//above is add by Morrison
// Check pets that's lost heartbeat

        if( !(local[1]%20))
       if(!find_object(VOID_OB))
                call_other(VOID_OB,"???");
        check_pets();
        call_out("init_cron", 60);
}
void autosave()
{
 object *user ;
 int i;
         user = users();
        message("channel:chat", HIY "\n【系统消息】:"+NOR+HIR+" 系统正准备记录你的档案。\n"NOR, users());
        for(i=0; i<sizeof(user); i++)
        user[i]->save();
        message("channel:chat", HIY "\n【系统消息】:"+NOR+HIG+" 你的档案已经被记录了。 \n" NOR, users());
}
void check_dns()
{
        mapping mud_list;
        mixed *muds;
        object dns;

        if(!dns = find_object(DNS_MASTER))
        // dns not started, not our problem
        return;
        mud_list = (mapping) DNS_MASTER->query_muds();
        muds=keys(mud_list);
        if(sizeof(muds)<= 1)
        { destruct(dns);
        call_other(DNS_MASTER,"???");
        }
        return;
}
void check_pets()
{
int i;
object ob,*ob_list;
ob_list=children("/clone/pet/pet");
for(i=0; i<sizeof(ob_list); i++) {
if( !ob = environment(ob_list[i]) ) continue;
ob->heal_up();
                }

return;
}

private void countdown(int min)
{
        min--;
        if( min )
        {
                call_out("countdown", 60, min);
        }
        else {
     message("system",HIR "。。。。。。。。。。。重新分布所有使命。。。。。。。。。。。" NOR,users());
            TASK_D->init_dynamic_quest(1);
            message("system",HIG "=======================所有使命分布完毕=======================\n" NOR,users());

        }
}
