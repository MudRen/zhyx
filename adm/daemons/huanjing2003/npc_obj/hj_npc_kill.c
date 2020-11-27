//                ��׼��������ʾ��                                   |
// �þ�������  ɱ¾�� �����һ�Я����ұ���Ѱ�ҵı��
// by naihe  2002-10-27  ��ï��
// naihe 05-9-4 15:43 �Ż�һ�£�ͬʱ����2������
// naihe 05-9-5 11:02 �ٴ��Ż�

#include <ansi.h>

inherit NPC;

#include "hj_settings/room_amount_hj.h"
#include "hj_settings/health_desc.h"
#include "hj_settings/get_hj_dir.h"
#include "hj_settings/hj_msg.h"

#define     NPC_NORMAL_SIZE         6       // ��ͨNPC�ķ�Χ���� 0~ SIZE-1
#define     NPC_ZUREN_INDEX         5       // ����NPC��������
#define     NPC_ZUZHANG_INDEX       6       // �峤NPC��������
#define     NPC_YL_WUSHI_INDEX      10      // ���� -- ��ʿ
#define     NPC_YL_CIKE_INDEX       7       // ���� -- �̿�
#define     NPC_YL_SHASHEN_INDEX    8       // ���� -- ɱ��
#define     NPC_YL_YINSHI_INDEX     9       // ���� -- ��ʿ

void checking();
void npc_dead_reward();
void npc_dead_reward_wushi();
void npc_dead_reward_sp( int total_reward );

// ��һ������ָ�����塱�� �ڶ�������ָ������
varargs void setme( int npc_class, int npc_level )
{
    int std_power, std_busy, std_hpmax;
    mapping *npc_info, *npc_info2, info;
    string id, *class_list;
    int i;
    // npc ��׼��Ϣ -----------------------------------------------------
    npc_info2 = ({
        ([ "name":"Сͷ��",
            "id":({ "tou ling", "ling", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // Խ��Խ������������
        ]),
        ([ "name":"��ʿ",
            "id":({ "li shi", "shi", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // Խ��Խ������������
        ]),
        ([ "name":"׳��",
            "id":({ "zhuang han", "han", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // Խ��Խ������������
        ]),
        ([ "name":"��ͽ",
            "id":({ "xiong tu", "tu", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // Խ��Խ������������
        ]),
        ([ "name":"��ʦ",
            "id":({ "fa shi", "shi", }),
            "auto_kill": 1,
            "hit_suck": 1,  // ��������ȡ hp
            "peaceful": (5+random(15)), // Խ��Խ������������
        ]),
        ([ "name":"����",
            "id":({ "zu ren", "ren", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // Խ��Խ������������
        ]),
        ([ "name":HIY"�峤",
            "id":({ "zu zhang", "zhang", }),
            "auto_kill": 1,
            "peaceful": (5+random(15)), // Խ��Խ������������
        ]),
        ([ "special_name": HIB"������"HIY"�̿�"NOR,
            "special_long" : "����һ��������Ĵ̿ͣ��������������ݣ��ý����ˡ�\n",
            "id":({ "youling cike", "cike", }),
            "auto_kill": 1,
            "peaceful": 3, // Խ��Խ������������
            //"hit_busy": 1, // ���������æʱ
            "dead_reward_score" : 150,    // NPC����ʱ����轱��
            "max_busy_limit" : 3,  // ��NPC���ֻ�ܽ��ܵ� busy time������ʱ��ǿ�ƻָ�����
            "del_msg" : "$N���ط���һ��������Х������ء���һ����ʧ�����ˡ�\n",
        ]),

        ([ "special_name": HIB"������"HIR"ɱ��"NOR,
            "special_long" : "����һ���������ɱ��ȫ��ɢ�����˵�ɱ����\n",
            "id":({ "youling shashen", "shashen", }),
            "auto_kill": 1,
            "peaceful": 3, // Խ��Խ������������
            "hit_busy": 1, // ���������æʱ
            "dead_reward_score" : 1500,    // NPC����ʱ����轱��
            "del_msg" : "$N���ط���һ��������Х������ء���һ����ʧ�����ˡ�\n",
        ]),
        ([ "special_name":HIB"������"HIM"��ʿ"NOR,
            "special_long" : "����һ�����������ʿ��ȫ��ɢ����һ��Ī����ѹ��֮�������˲��ҿ�����\n",
            "id":({ "youling yinshi", "yinshi", }),
            "hit_busy": 1, // ���������æʱ
            "dead_reward_score" : 800,    // NPC����ʱ����轱��
            "del_msg" : "$N���ط���һ��������Х������ء���һ����ʧ�����ˡ�\n",
        ]),
        ([ "special_name": HIB"��������ʿ"NOR,
            "special_long" : "����һ�����������ʿ����ɭ���졣\n",
            "id":({ "youling wushi", "wushi", "shi", }),
            "hit_busy": 1, // ���������æʱ
            "del_msg" : "$N��Ȼ����һ��̶����ɽ�����˲ʱ����Ӱ���ʣ���ʧ�����ˣ�\n",
        ]),
    });
    // npc ս�������Ϣ -----------------------------------------------------
    std_power = 15 + random( 6 );
    std_busy = 3 + random( 6 );
    std_hpmax = 50 + random( 251 );
    npc_info = ({
        ([ "power": std_power * 2,  "busy": std_busy,    "hpmax": 400+random(201) ]),  // Сͷ��    0
        ([ "power": std_power *3/2, "busy": std_busy,    "hpmax": std_hpmax       ]),  // ��ʿ      1
        ([ "power": std_power,      "busy": std_busy,    "hpmax": 300+random(201) ]),  // ׳��      2
        ([ "power": std_power,      "busy": 2+random(3), "hpmax": std_hpmax       ]),  // ��ͽ      3
        ([ "power": std_power,      "busy": 2+random(2), "hpmax": 80+random(71)   ]),  // ��ʦ      4
        ([ "power": std_power,      "busy": std_busy,    "hpmax": std_hpmax       ]),  // ����      5
        ([ "power": std_power * 3,  "busy": 3+random(4), "hpmax": 800+random(701) ]),  // �峤      6
        ([ "power": std_power / 2,  "busy": 1,           "hpmax": 1500+random(501) ]), // ����̿�  7
        ([ "power": std_power * 2,  "busy": 1+random(2), "hpmax": 8000+random(3001) ]),// ����ɱ��  8
        ([ "power": std_power * 3,  "busy": 2+random(3), "hpmax": 3000+random(1001) ]),// ������ʿ  9
        ([ "power": 10+random(21),  "busy": 2+random(2), "hpmax": 400+random(201) ]),  // ������ʿ  10
    });
    // ���´˴�����ʱ����Ҫ������ȷ��ֵ�������� help �ļ���
    // ---------------------------------------------------------------------------
    class_list = ({
        YEL"��Ұ��",
        YEL"������",
        YEL"������",
        YEL"ɽ����",
        YEL"������",
    });
    i = sizeof( npc_info2 );
    if( npc_class == 88 )  // ָ�����塱Ϊ����NPC  (���� hj_room1.c �����)
    {
        npc_class = -1;
        npc_level = NPC_YL_WUSHI_INDEX;    // ��ָ��Ϊ ������ʿ
        set("job_npc", 1 );
    }
    else if( npc_class == 99 ) // ָ�����塱Ϊ���
    {
        npc_class = random(5);  // ��ô�����
    }
    else if( npc_class < 0 || npc_class > 4 )   // ���ݴ���Ļ�
    {
        npc_class = random(5);  // ��ôҲ���
    }
    // ok. ѡ��  lv
    if( npc_class != -1 )  // ����ָ������NPC�Ļ����ż�������
    {
        // ʡ�Բ���������ʱ���������
        if( npc_level < 1 || npc_level > i )
        {
            npc_level = random( NPC_NORMAL_SIZE );    // ������һ������������NPC��
            if( !query("take_gem_npc") && random( 300 ) == 88 )
                npc_level = NPC_YL_SHASHEN_INDEX;     // ��С���ʳ���ɱ��
            else if( !query("take_gem_npc") && random(200) == 88 )
                npc_level = NPC_YL_YINSHI_INDEX;      // ��С���ʳ�����ʿ
            else if( !query("take_gem_npc") && random(100) == 88 )
                npc_level = NPC_YL_CIKE_INDEX;        // ��ͨ���ʳ��ִ̿�
            else if( random(20) == 8 )
                npc_level = NPC_ZUZHANG_INDEX;        // �����׳��ָ����峤
        }
        else
            npc_level --;  // ����Ϊָ���ļ�1 (����1ʱ��˼�������0��)
    }
    // ��ֹ����
    if( npc_level < 0 || npc_level > sizeof(npc_info2) )
    {
        npc_level = NPC_ZUREN_INDEX;  // ������������ʱ��ǿ�Ƹ�Ϊ����
        delete( "job_npc" );
    }
    // ���û������֡�ID��������
    info = npc_info2[ npc_level ];
    if( info["special_name"] )
    {
        set_name( info["special_name"], info[ "id" ] );
    }
    else
    {
        set_name( class_list[ npc_class ] + info["name"] + NOR, info[ "id" ] );
    }
    if( info[ "special_long"] )
    {
        set( "long", info[ "special_long"] );
    }
    else
    {
        set( "long", "����һ��"+class_list[ npc_class ]+NOR"������ʮ�ֺ�ս������˵���ײг��ԡ�\n");
    }
    set("auto_kill", info[ "auto_kill" ] );
    set("peaceful", info[ "peaceful"] );
    set("del_msg", info[ "del_msg" ] );
    set("hit_busy", info[ "hit_busy" ] );
    set("hit_suck", info[ "hit_suck" ] );
    set("dead_reward_score", info[ "dead_reward_score" ] );
    set("max_busy_limit", info[ "max_busy_limit" ] );
    set( "iii", npc_class );
    set( "npc_class", npc_class );
    set( "npc_level", npc_level );

    set("hj_game/npc","kill");
    // ����ս����ص���ֵ��
    info = npc_info[ npc_level ];
    // ����Ǵ��� npc �������ֲ����峤����ô����ΪСͷ�������(��������������ˡ���ʿ֮��)��
    if( query("id") != "zu zhang" && query("take_gem_npc") )
        info = npc_info[ 0 ];
    set( "mepower", info[ "power" ] );
    set( "att_busy", info[ "busy" ] );
    set_temp( "hj_hp_max", info[ "hpmax" ] );
    set_temp( "hj_hp",     info[ "hpmax" ] );
    set( "attack_busy", 0 );
    set("msg","ֻ����һ�������������Ա��߹���һ����Ŀ�����ļһ\n");
    set("gender","����");
    set("age",30+random(30));
    set("no_refresh",1);
    set("life_remain", query("delete_time_max") );
    // �ǳֱ���ʱ���峤ͣ��ʱ���ӳ�һ����ɱ����ʿ������
    id = query("id");
    if( !query("take_gem_npc") )
    {
        if( id == "zu zhang" )
            set("life_remain", query("delete_time_max") * 2 );
        else if( query("dead_reward_score" ) )  // ������н������ֵ����ͣ���ʹ֮���ʱ��ӳ�
            set("life_remain", query("delete_time_max") * 8 );  // Ϊ��ά�ָ���
    }
    // ǿ��ɾ�� auto kill ��ǡ�
    if( query( "take_gem_npc" ) || id == "youling wushi" || id == "youling yinshi" )
        delete( "auto_kill" );
    remove_call_out("checking");
    remove_call_out("delete_me");
    call_out("checking", 3 );
    if( id == "youling yinshi" || id == "youling shashen" )
        hj_shout( HIM"���þ����š���˵"+query("name")+HIM"�ڻþ������г����ˣ�\n"NOR );
}

void create()
{
    set("delete_time_max",300+random(180) );
    // ÿ��NPC����ʱ����� 8 ����(������ұ���Ŀ�꣬���� fyld_npc.h ������Ϊ׼��
    setme( 99 );
    setup();
}

// �Իٳ���
void delete_me()
{
    object ob = this_object();
    remove_call_out( "delete_me" );
    if( !objectp(ob) )
        return;
    if( !environment(ob) )
    {
        destruct(ob);
        return;
    }
    if( stringp( query("del_msg") ) )
        message_vision( query("del_msg"), ob );
    else
        message_vision( "ֻ����һ���ֽУ�$N���ء���һ����ʧ�����ˡ�\n", ob);
    // �������ر�� NPC Ҫͨ��һ�¡�����̿Ͳ���ͨ�棻������ʿ�� JOB NPC��Ҳ���ء�
    if( query("id") == "youling yinshi" || query("id") == "youling shashen" )
    {
        if( query("hp") < 1 )
        {
            if( stringp(query("killme_by")) )
            {
                object who;
                who = find_player( query("killme_by") );
                if( objectp(who) && environment(who) == environment(ob) )
                    hj_shout( HIM"���þ����š���˵"+query("name")+HIM"��"+who->query("name")+HIM"ɱ���ˣ�\n"NOR);
                else
                    hj_shout( HIM"���þ����š���˵"+query("name")+HIM"��ɱ���ˣ�\n"NOR );
            }
        }
        else
            hj_shout( HIM"���þ����š���˵"+query("name")+HIM"�뿪�˻þ����֡�\n"NOR );
    }
    destruct(this_object());
}

// �����������
void checking()
{
    object ob,*inv,temp,my_host,qxd;
    string *dirs, id;
    int i, ppp;

    object target;

    if( !environment(this_object()) ) return;

    if( query("take_gem_npc") =="yes" && stringp(query("the_gem_for")) )
    {
        my_host=find_player(query("the_gem_for"));
        if(!my_host || my_host->query_temp("huanjing") !="start" ||
           my_host->query_temp("hj_hp") < 1 ||
           my_host->query_temp("hj_find_ok") == "yes")
        {
            remove_call_out("delete_me");
            call_out("delete_me",1);
            return;
        }
    }
    // ����ʱ�����н�����
    if( query_temp("hj_hp") < 1 )
    {
        npc_dead_reward();
        return;
    }
    // ����ʱ�䵽�ˣ������뿪��û���κν�����
    if( query("life_remain") < 1 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1 );
        return;
    }
    ob = this_object();
    // �������æʱ���ƣ��������ڵ�æʱ�����Ƶ�Ҫ�ߣ���ôǿ�ƻָ�
    if( (ppp=query("max_busy_limit")) > 0 && ppp < query_busy() )
    {
        start_busy( ppp );
        message_vision( "\n$N����ʹ��һ���������ƺ��ָ������ɣ�\n\n", ob );
    }
    // ��NPC�����������濪ʼ���빥������
    // �����ȴ�ʱ����δ������ż���õ�С���ʵ��������������
    add("attack_busy", -1 );
    if( query("attack_busy") < 0 )
        set("attack_busy", 0 );
    if( query("attack_busy") || !random(8) )
    {
        add("life_remain", -1 );
        remove_call_out("checking");
        call_out("checking",1 );
        return;
    }
    // �ã���ʼ����
    // ����� killme_by ��ǣ�����������
    id = query("id");
    if( query("killme_by") )
    {
        target = present( query("killme_by"), environment(ob) );
        // Ŀ�겻�ڱ����ˣ��������״̬
        if(!target)
        {
            delete("killme_by");
            delete("start_kill_msg");
            set_leader( 0 );  // ֹͣ����
        }
        // Ŀ����ڱ��أ���
        else 
        {
            // ����䲻Я���������Լ���ʱ�뿪��������ʵ�и��棬���ҿ���
            if( !present("shenren ling",target) && !present( "hj temp leave obj", target ) )
            {
                set_leader( target );
                // ����ǵ�һ�ֿ�������֪ͨ
                if( !query("start_kill_msg") )
                {
                    set("start_kill_msg", 1);
                    message_vision( HIR"\n����$n"HIR"��Ҫɱ��$N"HIR"��\n\n"NOR, target, this_object() );
                }
                // ���ù����ȴ�ʱ��
                set("attack_busy", query("att_busy") );
                // ���ù���������
                call_out( "att_target",1, target );
            }
        }
    }
    // ���򣬿��ܽ�������������
    else if( query("auto_kill") )   // ���� npc �Ƿ���Զ� kill
    {
        inv = all_inventory(environment(ob));
        ppp = query( "peaceful" );
        if( ppp < 2 )
            ppp = 2;
        // �������
        for( i=sizeof(inv)-1; i>=0; i-- )
        {
            if( random(ppp) )  // ��ƽ�ȸߵľͲ����������(�������ǲ����ܴ�Ķ���)
                continue;
            // ����ִ���ж���׼������
            temp = inv[i];
            if( !temp->is_character()
              || temp->query("hj_game/npc")
              || temp->query_temp("hj_hp") <1
              || temp->query_temp("huanjing") != "start"
            )
                continue;
            // �޵��߲��򣨴���Ҳ�״�
            if(!(qxd = present("qixing deng",temp)) )
                continue;
            // Я���������Я����ʱ�뿪��(��ʱ�뿪��Ϸ)�ߣ����ᱻ������
            if( present("shenren ling",temp) || present( "hj temp leave obj", temp ) )
                continue;
            // ����4�����ϵĵ�����ʱ���峤�����������й�����
            if(  id == "zu zhang" && qxd->query("last_deng") > 4 )
                continue;
            // ����6�����ϵĵ�����ʱ��Сͷ�첻���������й�����
            if(  id == "tou ling" && qxd->query("last_deng") > 6 )
                continue;
            // ��ô����ʼ����Ŀ�꣡
            set_leader( temp );
            set("killme_by",temp->query("id") );
            message_vision( HIR"\n����$n"HIR"��Ҫɱ��$N"HIR"��\n\n"NOR,
                    temp, this_object() );
            set("start_kill_msg", 1);
            set("attack_busy", query("att_busy") );
            call_out("att_target",1, temp );
            break;
            // �����ã���С��    tell_object(find_player("naihe"),"�鲻�� kill "+temp->query("id")+" .\n");
        }
    }
    i = 0;  // ��Ϊ�Ƿ� random_move �ı��
    // ������ʿ�����ߴ������⽱����NPC����Ҫ��������
    if( id == "youling wushi" || query( "dead_reward_score" ) )
    {
        if( !random(50) )
            i = 1;
    }
    else if( !random(5) )
        i = 1;
    if( i && !is_busy() && !query("killme_by") && living(this_object()) && query_temp("hj_hp") > 0 )
    {
        dirs=({ "east","west","south","north","northeast",
            "northwest","southeast","southwest" });
        command( "go "+ dirs[random(sizeof(dirs))] );
    }
    add("life_remain", -1 );
    remove_call_out("checking");
    call_out("checking",1 );
}

void att_target( object target )
{
    object temp;
    string temp_msg,color_name, id;
    int power = query("mepower") * 4 / 5 + random( query("mepower") / 5 ) + 1;

    if( is_busy() || query_temp("hj_hp") < 1 )
        return;
    if( !target
      || !environment(target)
      || environment(target) != environment( this_object() )
      || target->query_temp("hj_hp") < 1 )
    {
        delete("killme_by");
        delete("start_kill_msg");
        set_leader( 0 );  // ֹͣ����
        return;
    }
    switch( random(12) )
    {
    case 0 .. 3 : temp_msg=NOR+CYN"�ݺݵػӳ�һȭ����$N"NOR+CYN"������У�";break;
    case 4 .. 7 : temp_msg=NOR+CYN"�ݺݵ��߳�һ�ţ�$N"NOR+CYN"�����������Ը����ţ�"; break;

    case 8: temp_msg=NOR+CYN"���С��������ֽУ�˫���һӣ�ȴҲ��$N"NOR+CYN"�����У�";
        power -= ( power /3 ); break;
    case 9:    temp_msg=NOR+CYN"�ֽ��һӣ���ȫ�����·���ȴҲ��$N"NOR+CYN"�����У�";
        power -= ( power /3 ); break;
    case 10:temp_msg=NOR+CYN"ʹ������������$N"NOR+CYN"һײ����$N"NOR+CYN"ײ�÷��˿�ȥ��";
        power += ( power / 2 ); break;
    case 11: temp_msg=NOR+CYN"����$N"NOR+CYN"һץ��$N"NOR+CYN"��������ֻ���˵����ˡ�";
        power = power / 5 + random( power / 5 );
        if( power < 1 ) power = 1;
        break;
    }
    // ��ʦ�����������಻��ͬ��
    if( (id=query("id")) == "fa shi" )
    {
        power = query("mepower") * 4 / 5 + random( query("mepower") / 5 ) + 1;
        message_vision( sprintf( HIY"\n$n"HIY"����$N"HIY"ָ�ֻ��ŵ�ʩ�ŷ���$N"HIY
            + "����ȫ����Ϣ��й������������ "HIR"%d"HIY" ����˺���\n"NOR, power ),
            target, this_object()
        );
    }
    else
        message_vision( sprintf( CYN"\n$n%s"NOR+CYN"������ "HIR"%d"NOR+CYN" ����˺���\n"NOR,
            temp_msg, power), target, this_object()
        );
    target->add_temp("hj_hp",-power);
    // ��������öԷ�����æʱ������
    if( query( "hit_busy" ) )
    {
        // ���֮�����⼼������֮һ����Ч�ֿ�����NPC�Ķ���๥����æʱЧ��
        if( !target->query_temp("hj_special/sh") && target->query_busy() < 3 && !random(5) )
        {
            target->start_busy( target->query_busy() + 5 );
            message_vision( HIB"$N"HIB"ֻ����һ����ľ֮�����㴫��ȫ����ʱ�������ã�\n"NOR, target );
        }
    }
    // ����ķ�ʦ����ȡ�Է��� hp.
    if( query( "hit_suck" ) )
    {
        if( !random(2) && query_temp("hj_hp") < (query_temp("hj_hp_max") *9 / 10 ) )
        {
            message_vision( "ֻ��$n������һ�ڴ�$N������й©��������$n����Ϣ�ָ�����ࡣ\n", target, this_object() );
            add_temp("hj_hp", power * 2 + random( power * 2 ) );
        }
    }
    // ȡ�����﹥��ʱ���ٷ���������
    //    target->add_temp("hj_score",-random(power/3) );
    //    if( target->query_temp("hj_score") < 1 )
    //    target->set_temp("hj_score", 1);
    color_name = get_health_desc( target->query_temp("hj_hp"), target->query_temp("hj_hp_max") );
    message_vision(NOR"�� $N"+color_name+""NOR" ��\n"NOR,target);
}

void hj_get_attack( object ob )
{
    if( !objectp(ob) || !query("dead_reward_score") )
        return;
    add( "hj_att/" + ob->query("id"), 1 );
}

// =================================================================
// ========================== NPC �������� =========================
// =================================================================
void npc_dead_reward()
{
    string id = query("id");
    object temp, me, ob = this_object();

    // ������� env �� hp ����(����ĵ���), ���κν�����
    if( !environment(ob) || query_temp("hj_hp") > 0 )
    {
        destruct( ob );
        return;
    }
    // ��һ���С�ĸ��ʣ���NPC���ܶ����Я�����
    if( random(200) == 88 )
        set("take_gem_npc", "yes" );
    // ����ǳֱ�NPC�����Ե��±��
    if( query("take_gem_npc") =="yes" )
    {
        temp = new(__DIR__"hj_obj_gem");
        temp -> setme( query("npc_class") );    // ��� class ��������Χ�����������ñ���
    }
    // ����������峤�����±����Ȩ�ȡ����������������JOB����൱�������ˡ�
    else if( id == "zu zhang" && random(3) )
    {
        temp = new( __DIR__"hj_obj_gem_qz" );
        temp -> setme( query("npc_class") );    // ��� class ��������Χ������������Ȩ��
    }
    // �����������������ʿ�����Ҳ��������⽱���ģ����л�����¼���ʯ���Ʒ���ﱦʯ��
    else if( !random(3) && id != "youling wushi" && !query("dead_reward_score") )
    {
        if( random(3) )
            temp = new( __DIR__"hj_obj_other" );
        else if( random(2) )
            temp = new( __DIR__"hj_obj_quest" );
        if( temp )
            temp->setme(99);
    }
    if( temp )
    {
        message_vision("$N����ͻȻ����һ"+temp->query("unit")+"$n��\n",ob,temp);
        temp->move(environment(ob));
    }
    // ��������Ľ�����������ʿ������NPC���ر���
    if( id == "youling wushi" )
        npc_dead_reward_wushi();
    // ��������С��������֡������ã���ʹ��Ԥ���ķ�ʽ�������֡�
    else if( query("dead_reward_score") )
        npc_dead_reward_sp( query("dead_reward_score") );
    // ��ɱ����NPC����ҼӸ���¼
    if( stringp( query( "killme_by" ) ) )
    {
        me = find_player( query("killme_by") );
        if( objectp( me ) )
            me->add( "huanjing2003/kill_npc", 1 );
    }
    remove_call_out("delete_me");
    call_out("delete_me",1 );
}
// =================================================================    


// ������ʿ��������轱����
// (1) query("job_master_obj")  object �ͣ�JOB�����ڴ��˵�
// (2) query("job_award_score") int �ͣ������ĵ÷�
// (3) query("job_award_skills") int �ͣ������ļ���
// query("killme_by")  ���һ��
void npc_dead_reward_wushi()
{
    object me, ob = this_object();
    mapping sks;
    string *sks_list, sks_id;

    if( query("id") != "youling wushi" )
        return;
    me = query("job_master_obj");
    if( !objectp(me)
      || query("killme_by") != me->query("id")
      || me->query_temp("huanjing") != "start"
      || me->query_temp("hj_hp") < 1
      || !environment(me)
      || environment(me) != environment(ob)
    )
        return;

    // ��������OK����ʼ�������
    message_vision(CYN"$N"NOR+CYN"�����˱��Լ��ų�������������ʿ�����д�ο��\n"NOR, me);
    // �Ƚ����÷�
    me->add_temp("hj_score", query("job_award_score") );
    tell_object( me, HIR"��Ϸ��ʾ����ĵ÷������� "+ query("job_award_score")+ " �㣡\n"NOR);
    // �ٽ������ܣ�����еĻ�
    if( query("job_award_skills") )
    {
        sks = me->query_temp("hj_game_skills");
        if( sizeof( sks ) )
        {
            sks_list = keys( sks );
            // ��ȡ������ļ��� ID
            sks_id = sks_list[ random(sizeof(sks_list)) ];
            // ���������������
            if( me->query_temp("hj_game_damages/" + sks_id ) )
            {
                me->add_temp("hj_game_damages/" + sks_id, query("job_award_skills") );
                tell_object( me, sprintf( HIR"��Ϸ��ʾ����ġ�%s�������� %d ����\n"NOR,
                    me->query_temp("hj_game_skills/"+sks_id),
                    query("job_award_skills"))
                );
                if( me->query_temp("hj_game_damages/"+ sks_id) > 99 )
                {
                    me->set_temp("hj_game_damages/"+ sks_id, 99);
                    tell_object( me, HIR"�ü����Ѿ��ﵽ�����ˡ�\n"NOR );
                }
            }
        }
    }
    // ��������������Ļ�
    if( query("job_award_power") > 0 )
    {
        me->add_temp("hj_game_mepower", query("job_award_power") );
        tell_object( me, sprintf( HIR"��Ϸ��ʾ�����������ǿ�� %d �㣡\n"NOR,
            query("job_award_power"))
        );
    }
    // End.
}
// =================================================================


// ����Ľ�������Ҫ�Ǹ� youling shashen �� youling yinshi �� youling cike ʹ�á�
void npc_dead_reward_sp( int total_reward )
{
    mixed ls;
    string id, *key;
    object usr, ob = this_object();
    int total_hit, percent, reward;

    if( total_reward < 100 )
        total_reward = 100;
    if( total_reward > 10000 )
        total_reward = 10000;
    if ( !query("dead_reward_score") )
        return;
    if( !mapp( (ls=query("hj_att")) ) || !sizeof(ls) )
        return;
    key = keys( ls );
    foreach( id in key )
    {
        total_hit += ls[ id ];
    }
    if( total_hit < 1 )
        return;
    foreach( id in key )
    {
        usr = find_player( id );
        if( !objectp(usr)
          || usr->query_temp("huanjing") != "start"
          || usr->query_temp("hj_hp") < 1
          || !environment(usr)
          || !environment(usr)->query("room_mark")
        )
            continue;
        tell_object( usr, HIG"\n��" + (ls[id] >= total_hit ? "��" : "������֮")
            + "��ɱ����"+query("name")+HIG"���е�������Ϊ���г�����\n"NOR );
        percent = ls[id] * 100 / total_hit;
        reward = total_reward / 100 * percent;
        // ����ͬһ�ط�ʱ���÷ּ��롣
        if( environment(usr) != environment(ob) )
            reward /= 2;
        if( reward < 1 )
            reward = 1;
        tell_object( usr, HIR"��Ϸ��ʾ����ĵ÷������� "+reward+" �㣡\n"NOR);
        usr->add_temp( "hj_score", reward );
        if( query("killme_by" ) == usr->query("id") )
        {
            tell_object( usr, HIG"ɱ��"+query("name")+HIG"�����һ��������ɵģ���õ��˸���Ľ�����\n"NOR );
            reward = total_reward / 10;
            tell_object( usr, HIR"��Ϸ��ʾ����ĵ÷������� "+reward+" �㣡\n"NOR);
            usr->add_temp( "hj_score", reward );
        }
    }
    // End.
}
// =================================================================
// =================================================================
// =================================================================
