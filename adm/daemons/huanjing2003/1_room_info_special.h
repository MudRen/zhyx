/*********************************************************
   ���ļ�ֻ�� hj_room1.c ʹ�á�

   ��������������ͼƬ������Ч�������κ���ʹ�����ã���
   zmud4.62 32bit �����棬 ���壬С��(12)��С��(10) �鿴��
   �ɵ����Ч����

   ������֧������ JOB��

   ��һ��ɱ�˸�����峤ʱ��������õ������Ȩ�ȣ��Ѽ�����
         ���Ȩ�ȣ��ٻ������﷢�� JOB1_NEED_IDLE �룬����
         �õ�����������

   ������ڴ˷��� JOB2_NEED_IDLE �룬���õ� ������ʿ JOB��
         ɱ�������Եõ�����Ľ���������������ɱȥ������ͨ
         �����NPCЧ��һ��������ɱ����������ʿʱ���ɵõ�
         ������������Ϸ�÷֡�

   JOB1 �ķ�����Чʱ������ JOB2 �Ķ̡����忴�±ߵ����á�

   ���⣬�ڴ˷���ͣ�����������ʧ hp ���������ݣ� 

   int query_idle( object target ) ���ط���ֵ :)

   naihe 23:43 03-10-20
**********************************************************/


#include    "npc_obj/hj_settings/room_amount_hj.h"


#define        JOB1_NEED_IDLE       20
#define        JOB2_NEED_IDLE       31
#define        JOB1_AWARD           800
#define        JOB2_AWARD           80
#define        JOB2_AWARD_SKILLS    2

void full_all( object me );

int me_ok( object me )
{
    if( !me || !environment(me) || environment(me) != this_object()
      || me->query_temp("huanjing") != "start" || me->query_temp("hj_hp") < 1 )
        return 0;

    return 1;
}


void create()
{
    set("j1_time", JOB1_NEED_IDLE );
    set("j2_time", JOB2_NEED_IDLE );

    set("room_mark",mark);
    set("short",MAG"�þ�"NOR+GRN"����ʧ֮��������֮��"NOR);

    set("long", "����߹�����ȴ����������һС��ˮ̶��ˮ̶֮ˮ����ƽ����̶������һ��
Сͤ(ting)����ֻ����ɫ��磬�Թ���˸���˵������ĳ����������ޱȡ����ƺ�
�����������е���ɱ˻�����ղŵĽ��Ⱦ����������ȥ��
                                                           [1;33m��[37;0m       
                                                                    
                                            [1;32m.. .[37;0m      [1;34mI[37;0m       [1;32m..[37;0m    
                                            [1;32m..[37;0m      [1;34m,'.`.[37;0m           
                                              [1;34m.__,-'.:::.`-.__,[37;0m  [1;32m.[37;0m  
                                               [1;34m~-------------~[37;0m      ");

    // string to long, Ҫ�ֿ��� set, 5555555
    set("long", query("long") + "
                                                 [1;31m_|=|___|=|_[37;0m        
                                           [1;34m.__,-'.:::::::::.`-.__,[37;0m  
                               [37m[37;0m             [1;34m~-------------------~[37;0m   
                               [37m |[37;0m              [1;31m_|_|_|___|_|_|_[37;0m      
                               [37m###################################[37;0m  
[42m     [30m�y�z�{�|�}�~�}�|�{�|�}�|�{�z�y�x�y�z�{�|�}�~���~�}�|�{�z�y�x   [37;0m
        \n");

    // �κ�ע����ͼ�����Թ�����BBS����ɫ�������䲢�޶��¡�ͤ�ⰶ�ߵ�һ�����Ҽ��ϵģ�
    // Ϊ��һЩ������Ч����
    // ����ԭ����˭�ˣ��� HJ ������ҵ��;֮ʱ�����ͼ��������
    // ��ͼ�����κεĵ����ϵ� welcome ͼ��HOHO����ϧ�ҶԻ��������
    // ���޸о������⻭���Ƕ�����������Ч����
    // zmud4.62 32bit �����棬 ���壬С�ģ�12�� �鿴���ɵ����Ч����
    // naihe 23:25 03-10-20

    set("item_desc",([
        "ͤ"   : "����һ��Сͤ�ӣ����·��š�ͤ�ⰶ������һ��Ȩ��(zhang)��ʮ�ִִ�\n",
        "Сͤ" : "����һ��Сͤ�ӣ����·��š�ͤ�ⰶ������һ��Ȩ��(zhang)��ʮ�ִִ�\n",
        "ting" : "����һ��Сͤ�ӣ����·��š�ͤ�ⰶ������һ��Ȩ��(zhang)��ʮ�ִִ�\n",
        "��"   : "����һ��Ȩ�ȣ��ƺ�ɢ����һ�ɹ������Ϣ�����ϱ߿���һЩС��(zi)��\n",
        "Ȩ��" : "����һ��Ȩ�ȣ��ƺ�ɢ����һ�ɹ������Ϣ�����ϱ߿���һЩС��(zi)��\n",
        "zhang": "����һ��Ȩ�ȣ��ƺ�ɢ����һ�ɹ������Ϣ�����ϱ߿���һЩС��(zi)��\n",
        "��"   : "������֮��Ȩ�� -- �������ʿ���ɴ˽��٣���ҹ�����ּ���չ����ս��\n",
        "С��" : "������֮��Ȩ�� -- �������ʿ���ɴ˽��٣���ҹ�����ּ���չ����ս��\n",
        "zi"   : "������֮��Ȩ�� -- �������ʿ���ɴ˽��٣���ҹ�����ּ���չ����ս��\n",
        ]) );

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("exits",([
        "east" : __DIR__"hj_room2", 
        "south" : __DIR__"hj_room11",
        "southeast" : __DIR__"hj_room12",
        ]) );

    setup();
}

void init()
{
    // ���еĹ��ж���(�� all_room_info_hj.h �� 1_room_info_special.h ����)
#include "all_common_init.h"

    // �������ܣ�����
    add_action("do_lvup", ({ "levelup", "lvup" }) );
    // npc ����˵أ�������ʲô�ˣ������뿪
    if( me->query("hj_game/npc") )
        call_out("npc_out", 1, me);
    // ������� me �ĳ���
    if( me->query_temp("huanjing") == "start" )
        call_out( "start_check", 2, me, me->query("id") );
}

// ���еĹ��к���(�� all_room_info_hj.h �� 1_room_info_special.h ����)
#include "all_common_func.h"

void npc_out( object me )
{
    object outroom;
    int or;

    if( !me ) return;
    if( !environment(me) || environment(me) != this_object() )
        return;

    message_vision("$N���ҿ���һ�£�����ææ���뿪�ˡ�\n", me);
    if( random(2) ) or = 2;
    else if( random(2) ) or = 11;
    else or = 12;

    outroom = find_object( __DIR__"hj_room"+or );
    if( !outroom ) outroom = load_object( __DIR__"hj_room" + or );
    me->move( outroom );
    message_vision("$N����ææ�����˹�����\n", me);
}

void start_check( object me, string id )
{
    if( !me_ok(me) )
    {
        delete("checking_job1_"+ id );
        delete("checking_job2_"+ id );
        delete("checking_lost_hp_"+ id );
        return;
    }

    // ��ʼִ�д��˵ķ����жϼ���Ѫ����

    // ��δ��ִ�� checking ���˵� job1 ���������Խ���
    if( !query("checking_job1_"+ id ) )
    {
        set("checking_job1_"+ id, 1);
        call_out( "checking_job1", 5 + random(6), me, id);
    }
    // ͬ��
    if( !query("checking_job2_"+ id ) )
    {
        if( !me->query_temp("hj_youling_job") )
        {
            set("checking_job2_"+id, 1);
            call_out( "checking_job2", 5 + random(6) , me, id );
        }
    }
    // ͬ�ϼ�����
    if( !query("checking_lost_hp_"+id) )
    {
        set("checking_lost_hp_"+ id, 1);
        call_out( "lost_hp", 1, me, id );
    }
}

// ������ص�ͣ�����᲻�ϵص�HP��ֱ����Ϊֹ��
void lost_hp( object me, string id )
{
    if( !me || !me_ok(me) )
    {
        delete("checking_lost_hp_"+ id );
        return;
    }

    // ��� lost hp.
    if( random(3) )
    {
        call_out("lost_hp", 5+random(6), me, id );
        return;
    }

    write(HIB"����ظе�һ��ǿ�ҵĹ�����Ϣ��֪���Ķ�ɢ��������ֻ�����ķ����ƣ���������������Լ�Զ��һ�㣡\n"NOR);
    me->add_temp("hj_hp", -(5+random(16)) );
    call_out("lost_hp", 5+random(6), me, id);
}

// �����Ѽ�����Ȩ�ȵ� JOB��
void checking_job1( object me, string id )
{
    string *job1_ids, msg;
    object *job1_obj_list, temp;
    int i, award_score;

    // ���ߵ���ҵ��� query_idle() ��� bug
    if( !me || !me_ok(me) || !interactive(me) )
    {
        delete("checking_job1_"+ id );
        return;
    }
    if( query_idle(me) < JOB1_NEED_IDLE )
    {
        call_out("checking_job1", 5+random(6), me, id);
        return;
    }

    // ����ʱ�䵽
    job1_ids = ({ "manye quanzhang", "mengli quanzhang", "aiyao quanzhang",
            "shanguai quanzhang", "juren quanzhang", });

    job1_obj_list = ({ });

    // �鿴���Ƿ���ȫ��Ȩ��
    for( i=0;i<sizeof( job1_ids ); i++ )
    {
        temp = present( job1_ids[i] , me );

        // �����κ�һ���������˳�������
        if( !temp )
        {
            delete("checking_job1_" + id );
            return;
        }
        job1_obj_list += ({ temp });
    }
    // �õģ���ý�����
    message_vision( HIY"$N"HIY"��������ϸ˼�������Լ�����Ȩ�ȶ�������ҫ�۹�â����Լ��ͬ��ָ���������Ȩ�ȣ�\n"NOR,me);
    msg = HIY + "";
    // Ȩ��û����ɫ�����ã����Զٺ�����Ҳ����д��ɫ�ˡ�
    for( i=0; i<sizeof( job1_obj_list ); i++ )
    {
        if( i == 0 )
            msg += job1_obj_list[i] -> name(1);
        else msg += sprintf( "��%s", job1_obj_list[i] -> name(1) );
        destruct( job1_obj_list[i] );
    }

    message_vision( msg +"����\nֻ������Ȩ�Ƚ����ɳ�������ɶ��˻��ײ��������Ȩ�ȣ���ȫ����ʧ�����ˣ�\n$N"HIY"�ۿ��˾�������Ī����ֻ����˵����������\n"NOR, me );

    delete("checking_job1_"+ id );
    award_score = JOB1_AWARD + random( JOB1_AWARD / 10 );
    me->add_temp("hj_score", award_score );
    tell_object( me, HIR"��Ϸ��ʾ����ĵ÷������� "+award_score+" �㣡\n"NOR );
    return;
}

// ����ȥɱ��������ʿ��JOB��
void checking_job2( object me, string id )
{
    object kill_npc, rooms, ling;
    int random_room, yeah = 0;

    // ��� me ���������������� me �Ѿ��� JOB �����ˣ�������⺯����
    // ��� JOB ����� object �͵ģ���NPC������ɱ�ˣ�JOB���Զ����� :)
    if( !me || !me_ok(me) || me->query_temp("hj_youling_job") || !interactive(me) )
    {
        delete("checking_job2_"+ id );
        return;
    }
    // ����һ���ر��жϡ�����ҳɹ��ӳ��񴦵õ��������Ҫ��ϲ���ʱ��
    // ���ɵõ�һ��������֮����д��������ߣ������Լӱ��ٶȵõ���ʿJOB��
    // ������������ڸ���ҵġ����������Я�����������ַ�������δִ��
    // �Իٳ���������������������Ч�ķ�BUG�����
    ling = present( "youling ling", me);
    if( ling && ling->query("my_master") == me
        && ling->query("this_time_mark") == me->query_temp("this_time_mark") )
    {
        yeah = 1;
        if( query_idle(me) < JOB2_NEED_IDLE/2 )
        {
            call_out("checking_job2", 5+random(6), me, id);
            return;
        }
    }
    if( !yeah && query_idle(me) < JOB2_NEED_IDLE )
    {
        call_out("checking_job2", 5+random(6), me, id);
        return;
    }

    if( yeah && ling )
        message_vision( HIB"$N"HIB"���ϵ�$n"HIB"��Ȼ����һ�����֮������Χ���������������������һƬ��Ӧ��\n"NOR, me, ling);

    // �ɹ�������JOB��
    delete("checking_job2_"+id);
    kill_npc = new( __DIR__"npc_obj/hj_npc_kill" );
    kill_npc->setme( 88 );  // ����� set.

    kill_npc->set( "job_master_obj" , me );
    kill_npc->set("job_award_score", JOB2_AWARD * 9 / 10 + random( JOB2_AWARD / 5 ) );
    switch( random(10) )
    {
        // ������������ me ��ĳ����������ټ�
        case 0..1 :kill_npc->set("job_award_skills", JOB2_AWARD_SKILLS + random(2) );
            break;
        // ���߽���һ����������Ϊ����ֵ����Ҫ�����Բ��ɶཱ
        case 8 :kill_npc->set("job_award_power", 1 );
            break;
    }
    // ����һЩ����������Ҳ�����Դ�Ϊ���ݣ��ж��Ƿ��Լ���NPC����Ҫ�״򣨺��Ѵ򣡣���
    kill_npc->set("gender", me->query("gender") );
    kill_npc->set("long", kill_npc->query("long") + "���˿���������"+me->query("name")+"һģһ����\n");
    kill_npc->set("per", me->query("per") );

    random_room = 2 + random( HJ_ROOM_AMOUNT -1 );
    rooms = find_object( __DIR__"hj_room" + random_room );
    if( !rooms ) rooms = load_object( __DIR__"hj_room" + random_room );
    kill_npc->move( rooms );
    message_vision( BLU"����һ����������$N"NOR+BLU"��Ȼ��������֮����\n"NOR, kill_npc);
    // JOB �����ɸ� npc ʵ�֡�

    me->set_temp("hj_youling_job", kill_npc);
    // �� me ���ñ�ǣ������������JOB��
    // �� object ��������JOB������NPC����(destruct)ʱ��JOB��Ȼ������

    message_vision( BLU"\n$N"NOR+BLU"��������ϸ˼����Ȼ��ֻ��������֮��Ȩ�ȷ���һ���ɽ�֮����\n"
        "һ��ģ����Ӱ�Ӵ�Ȩ���м����������Ȼ����$N"NOR+BLU"�����壬����߼����ȥ��\n"
        "$N"NOR+BLU"����δ�������Ѵ�ס������м���Ӱ���ƺ����� "HIR"\""+random_room+"\""NOR+BLU" ȥ�ˡ�\n\n"NOR, me);
    me->start_busy(3);
    // ok,finish.
}

// �ǳ��ѵ������ƶ�
// naihe 05-9-3 18:18 ���������ֲ��Ǻ��ѡ���5��嵽 lv6, lv6 ��ʲô���������ǿ����
// ��������Ѷȡ�
int do_lvup(string arg)
{
    object me = this_player(), rooms;
    int next_lv, score_need, skills_need, power_need, f_sks_need, y_sks_need, l_sks_need, d_sks_need, heal_sks_need, dh_sks_need, fh_sks_need, gs_sks_need;
    string msg;

    int t;

    if( !me_ok(me) ) return 0;

    if( me->is_busy() || me->query_temp("hj_need_waiting") )
        return notify_fail("�㻹æ���أ���ô��Ҫ�����黹�ǵ��пյ�ʱ����˵�ɡ�\n");

    next_lv = me->query("huanjing2003/lv") + 1;
    if( next_lv > 9 ) return notify_fail("�������Ѿ�����ߵĵȼ��ˣ�\n");

    rooms = find_object( __DIR__"room_door_hj" );
    if( !rooms ) rooms = load_object( __DIR__"room_door_hj" );
    if( !rooms ) return notify_fail("����˭������������\n");

    switch( next_lv )
    {
// ######################################################
// ��ʱ�����κ��Զ����֣�����������

        case 1: msg = "1001��÷�"; score_need = 1001;
            break;


// ######################################################
// ��ʱ��sks �ѿ��Զ����� 5 lv
// ���ڵ� power ����������ȥ������ power ��㶨Ϊ21�㡣

        case 2: msg = "1001��÷֣��硢�ꡢ�ס��缼�ܸ�31����21������";
                score_need = 1001; t = 31; power_need = 21;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
            break;


// ######################################################
// ��ʱ��sks �ѿ��Զ����� 10 lv

        case 3: msg = "1001��÷֣��硢�ꡢ�ס��缼�ܸ�41����26������";
                score_need = 1001; t = 41; power_need = 26;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
            break;


// ######################################################
// ��ʱ��sks �ѿ��Զ����� 15 lv
// ����һ���ؼ��㣬���˱�����sks lv �ɱ��� 20��������
// ʹ�� yun ���⼼�����ԣ�Ҫ���Щ

        case 4: msg = "999 ��÷֣��硢�ꡢ�ס��硢�ָ�����ꡢ�ɻ�"
                        "��ʯ���ܸ�41����31������";
                score_need = 999; t = 41; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ��ʱ��sks �ѿ��Զ����� 20 lv

        case 5: msg = "1001��÷֣��硢�ꡢ�ס��硢�ָ�����ꡢ�ɻ�"
                        "��ʯ���ܸ�51����31������";
                score_need = 1001; t = 51; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ��ʱ��sks �ѿ��Զ����� 25 lv
// ������������� lv 5 һ���������������Щ��

        case 6: msg = "1001��÷֣��硢�ꡢ�ס��硢�ָ�����ꡢ�ɻ�"
                        "��ʯ���ܸ�51����31������";
                score_need = 1001; t = 51; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ��ʱ��sks �ѿ��Զ����� 30 lv

        case 7: msg = "1001��÷֣��硢�ꡢ�ס��硢�ָ�����ꡢ�ɻ�"
                        "��ʯ���ܸ�61����36������";
                score_need = 1001; t = 61; power_need = 36;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ��ʱ��sks �ѿ��Զ����� 35 lv
// ������һ���ؼ��㣬up lv �󣬽��ɱ��� sks 40, ������ pfm.
// �ر��ѣ�
        case 8:msg = "88��÷֣��硢�ꡢ�ס��硢�ָ�����ꡢ�ɻ�"
                        "��ʯ���ܸ�88����41������";
                score_need = 88; t = 88; power_need = 41;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ��ʱ��sks �ѿ��Զ����� 40 lv
// ��������һ�������������ϣ��ǵ�����ͦ�� :)
// ��Ϊ������Ҫ�󽵵���
// sks ��Ҫ������״ﵽ�ģ�hoho

        case 9:msg = "1888��÷֣��硢�ꡢ�ס��硢�ָ�����ꡢ�ɻ�"
                        "��ʯ���ܸ�66����31��������\n"
                "�����������������еļ��ܡ����������������";
                score_need = 1888; t = 66; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;
    }

// ######################################################
// ######################################################
// ######################################################


    write( "�㽫������ "+next_lv+" ������Ҫ "+msg+" ��\n");
    if( !arg || arg != "now")
        return notify_fail("��ȷʵ�������������� <levelup now> �������󣬽����Ӧ������������ĸ�����������������\n");

// ��ʼ����

    if( score_need && me->query_temp("hj_score") < score_need )
        return notify_fail("��û���㹻�ĵ÷֡�\n");

    if( power_need && me->query_temp("hj_game_mepower") < power_need )
        return notify_fail("��û���㹻��������\n");

    if( f_sks_need && (!me->query_temp("hj_game_skills/hfzj")
              || me->query_temp("hj_game_damages/hfzj") < f_sks_need) )
        return notify_fail("��ġ�����֮�����ȼ�������\n");

    if( y_sks_need && (!me->query_temp("hj_game_skills/hyzj")
              || me->query_temp("hj_game_damages/hyzj") < y_sks_need) )
        return notify_fail("��ġ�����֮�����ȼ�������\n");

    if( l_sks_need && (!me->query_temp("hj_game_skills/llzj")
              || me->query_temp("hj_game_damages/llzj") < l_sks_need) )
        return notify_fail("��ġ�����֮�����ȼ�������\n");

    if( d_sks_need && (!me->query_temp("hj_game_skills/ydzj")
              || me->query_temp("hj_game_damages/ydzj") < d_sks_need) )
        return notify_fail("��ġ�����֮�����ȼ�������\n");

    if( heal_sks_need && (!me->query_temp("hj_game_skills/heal")
              || me->query_temp("hj_game_damages/heal") < heal_sks_need) )
        return notify_fail("��ġ��ָ�֮�����ȼ�������\n");

    if( dh_sks_need && (!me->query_temp("hj_game_skills/dhzj")
              || me->query_temp("hj_game_damages/dhzj") < dh_sks_need) )
        return notify_fail("��ġ����֮�����ȼ�������\n");

    if( fh_sks_need && (!me->query_temp("hj_game_skills/fhzj")
              || me->query_temp("hj_game_damages/fhzj") < fh_sks_need) )
        return notify_fail("��ġ��ɻ�֮�����ȼ�������\n");

    if( gs_sks_need && (!me->query_temp("hj_game_skills/gszj")
              || me->query_temp("hj_game_damages/gszj") < gs_sks_need) )
        return notify_fail("��ġ���ʯ֮�����ȼ�������\n");

// all ok now!

    me->set("huanjing2003/lv", next_lv );
    if( score_need ) me->add_temp("hj_score", -(score_need-1) );
    if( power_need ) me->add_temp("hj_game_mepower", -(power_need-1) );
    if( f_sks_need ) me->add_temp("hj_game_damages/hfzj", -(f_sks_need-1) );
    if( y_sks_need ) me->add_temp("hj_game_damages/hyzj", -(y_sks_need-1) );
    if( l_sks_need ) me->add_temp("hj_game_damages/llzj", -(l_sks_need-1) );
    if( d_sks_need ) me->add_temp("hj_game_damages/ydzj", -(d_sks_need-1) );
    if( heal_sks_need ) me->add_temp("hj_game_damages/heal", -(heal_sks_need-1) );
    if( dh_sks_need ) me->add_temp("hj_game_damages/dhzj", -(dh_sks_need-1) );
    if( fh_sks_need ) me->add_temp("hj_game_damages/fhzj", -(fh_sks_need-1) );
    if( gs_sks_need ) me->add_temp("hj_game_damages/gszj", -(gs_sks_need-1) );

    if( me->query_temp( "hj_game_mepower") < 5 )
        me->set_temp( "hj_game_mepower", 5 );
    me->set("huanjing2003/last_power", me->query_temp("hj_game_mepower") );
    me->set("huanjing2003/last_skills_lv", me->query_temp("hj_game_damages") );

// 9������������ۻ������ۻ���������Ч
    if( next_lv == 9 )
    {
        me->delete("huanjing2003/last_power");
        me->delete("huanjing2003/last_skills_name");
        me->delete("huanjing2003/last_skills_lv");
        me->delete("huanjing2003/last_hp_max");
        me->delete_temp("hj_game_skills");
        me->delete_temp("hj_game_damages");
        me->set_temp("hj_game_mepower", 10 );
        me->set_temp("hj_hp_max", 700);
        me->set_temp("hj_game_skills/heal", "�ָ�֮��");
        me->set_temp("hj_game_damages/heal", 3+random(8) );
    }

    me->save();
    me->start_busy(5);

    message_vision( HIW"\n\n$N"HIW"���һ���������ĵ�����������磬�����һ����������֣�������������\n\n"
        "ֻ��$N"HIW"ȫ��������ҫ��������Ϊ���Ե�����һ����Σ�\n\n\n"NOR, me);

    rooms->save_player_level( me->query("name"), me->query("id"), me->query("huanjing2003/lv"), time() );
    return 1;
}
