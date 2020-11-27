#include <ansi.h>
#include <command.h>
#include <globals.h>
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
        message("system", HIY "\n��ϵͳ��Ϣ��:"+BLINK HIR+" ϵͳ��������Ӻ����·���ʹ����\n"NOR,users());
        call_out("countdown", 20, 5);
}

//--------------------------------------------------------------------
//�޸����ϵ�һ���аٷֺź������(�������60����1Сʱ)�Ϳ����޸�task���·ֲ���ʱ������ˡ�
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
        message("channel:chat", HIY "\n��ϵͳ��Ϣ��:"+NOR+HIR+" ϵͳ��׼����¼��ĵ�����\n"NOR, users());
        for(i=0; i<sizeof(user); i++) 
        user[i]->save();
        message("channel:chat", HIY "\n��ϵͳ��Ϣ��:"+NOR+HIG+" ��ĵ����Ѿ�����¼�ˡ� \n" NOR, users()); 
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
     message("system",HIR "�������������������������·ֲ�����ʹ������������������������" NOR,users());
            TASK_D->init_dynamic_quest(1);
            message("system",HIG "=======================����ʹ���ֲ����=======================\n" NOR,users());

        }
}
