//                ��׼��������ʾ��                                   |
/*****************************************************
         �þ�������  ������  �������£�

 �ɹ����ͣ��Իþ���֮��ʯ����֮���ȱ�ʯ���⣩ �� �þ�
           ����Ϸ�÷ֹ��򣩣�
   ���пɹ���֮���ϣ��� obj_copy.h ͬ����������ʦ����ͬ����

 �����ͣ�������·��ͯ��������֮����  ��Ҫð��ʱ��ʧ
         ��������𵴵�������뿪���򱻹���ʱ�������ܵȣ�
         �����۳��÷ֵķ���

 ���������Ͳ�����ϸ���ܡ�

 �ش������ͣ�����˿ɻ�ûþ��ڷ��� ����Ϸ��ͳ�ƽ�����
             ��ʧ�������м�����æʱ�����������������
             �����ģ�20�룻δ�ش�ģ�30�룻δ�ش��
             �ֲ�֪���ﵽ����ȥ�˵ģ��Զ����ţ�60�롣��
             ʵ���ϣ���������ڿ�ʼд��һ����������䣩
             ��ʱ����п��ǵ��ˣ���� ���ǵ� �����
             ���൱����������Ϊ������ʱ��ʹ������ֵ��
             ��Ҷ�ǿ��ͣ���ķ����������ǵ�����ʱ����
             �������籾NPC�Իٺ��޷�ִ��ɾ������ʹ��
             �Ʊ���� checking ���е㻭�������ζ������
             ��ʹ�ô��밲ȫ������æʱ��


 �����ͣ���������  ��Ϊ�����ǿ����

 �ؽ������鱦��    �����͡�
16:14 03-10-19
*****************************************************/

// by naihe  2002-10-29  ��ï��

#include <ansi.h>

inherit NPC;

#include "hj_settings/obj_list.h"
#include "hj_settings/room_amount_hj.h"
#include "hj_settings/obj_copy.h"
#include <set_del_color.h>

mapping list_temp;


string *names=({
    "�����̷�",
    "С��ͯ",
    "����",
    "����",   // �е�����Ի���ҵ�ζ������ :)
    "�����̷�",  // �����̷��Ļ���Ӵ���
    "�ؽ���",
    "�鱦��",
});

string *ids=({
    "shang fan",
    "hai tong",
    "lao ren",
    "lao ren",
    "shang fan",
    "cangjian sheng",
    "zhubao ke",
    "С��ͯ",
});

string *ids2 = ({
    "fan",
    "tong",
    "ren",
    "ren",
    "fan",
    "sheng",
    "ke",
    "tong",
});

string *quests=({
    "����",
    "Ϊʲô�ż�",
    "����",   // ���NPC���������������������
    "Ӣ��",
    "����",
    "�ؽ�",
    "�鱦",
    "Ϊʲô�ż�",
});

string *longs=({
    "����һ���������С�̷������۸�ʽ����Ʒ��\n������������ڡ�"+quests[0]+"�������顣\n",
    "����һ���������СŮ���ӣ���֪��Ϊʲô������һ����ɫ�ż���ģ����\n������������ڡ�"+quests[1]+"�������顣\n",
    "����һ���׷��ԲԵ����ˣ���ȴ������ȵ�ʮ��ǿ�������ӡ�\n������������ڡ�"+quests[2]+"�������顣\n",
    "����һ���׷��ԲԵ����ˣ���ɷ��������֪ʮ��Ԩ�������ӡ�\n������������ڡ�"+quests[3]+"�������顣\n",
    "����һ���������С�̷������۸�ʽ����Ʒ��\n������������ڡ�"+quests[4]+"�������顣\n",
    "����һ���������������ˣ���������һ��������\n������������ڡ�"+quests[5]+"�������顣\n",
    "����һ����̬����������ˣ��������ֵ�һ����թģ����\n������������ڡ�"+quests[6]+"�������顣\n",
    "����һ���������СŮ���ӣ���֪��Ϊʲô������һ����ɫ�ż���ģ����\n������������ڡ�"+quests[7]+"�������顣\n",

});

string *genders=({
    "����",
    "Ů��",
    "����",
    "����",
    "����",
    "����",
    "����",
    "Ů��",
});

string *ChatMsg=({
    "�ٺ�Ц��������������һЩ�ö�������˭Ҫ����һ�㣿��\n",
    "�Ĵ������ţ���ɫ��ʮ���ż���ģ���������Ҫ�����Ƶġ�\n",
    "���Ǻǡ���Ц�˼�������������������������ģ��Ǻǡ���\n",
    "���������ӣ�Ц�������������������У�������������֮�£�ȴ��֪�����֣���\n",
    "�ٺ�Ц��������������һЩ�ö�������˭Ҫ����һ�㣿��\n",
    "����̾�����������ɲ�֪��ʱ���ܼ�����Щ��������\n",
    "����̾�����������ɲ�֪��ʱ���ܼ�����Щˮ������\n",
    "�Ĵ������ţ���ɫ��ʮ���ż���ģ���������Ҫ�����Ƶġ�\n",
});

int *times=({
    5+random(6),
    3,
    5,
    1,
    5+random(6),
    1,
    1,
    3,
});

int *ages=({
    18+random(30),
    11,
    82,
    82,
    18+random(30),
    39+random(3),
    41,
    11,
});

int *del_me_time = ({
    600, 
    180,
    180,
    300,
    600,
    600,
    600,
    180,
});


int ask_help();

string *sell_kind=({"������","��Ʒ��","����","����", });


int me_ok(object me)
{
    object inv_me;
    int iii = query("iii");

    if( !me ) return 0;
    if( !me->query_temp("huanjing") || me->query_temp("huanjing") != "start" ||
        !me->query_temp("hj_hp") || me->query_temp("hj_hp") <1 ||
        !me->query_temp("hj_hp_max") )
         return 0;
    inv_me = environment(me);
    if( !inv_me || !inv_me->query("room_mark") )
        return 0;

    if( ( iii == 0 || iii == 4 || iii == 5 || iii = 6 ) && !query("job_set_finish") )
        return 0;

    return 1;
}


void setme( int iii )
{
    if( iii == 99 ) iii = random( sizeof(names) );
// �˾�����ã�����ֻ���ؽ������鱦��
//    iii = 5 + random(2);
    set("iii", iii );

    set_name(names[ iii ],({ ids[ iii ], ids2[ iii ] }));
    set("long",longs[ iii ]);
    set("hj_game/npc","quest");
    set("msg",query("name")+"���˹�����\n");
    set("gender",genders[ iii ]);
    set("my_quest",quests[ iii ]);
    set("use_times",times[ iii ]);
    set("age",ages[ iii ]);
    set("no_refresh",1);

    set("inquiry",([
        quests[ iii ] : (: ask_help :),
        ]));

    set("chat_chance",1); 
    set("chat_msg",({ query("name")+ChatMsg[ iii ] }) );

    remove_call_out("delete_me");
    remove_call_out("random_move");
    remove_call_out("start_my_job");
    call_out("start_my_job", 1 );
}


void create()
{
    setme( 99 );
    setup();
}

void start_my_job()
{
    int q_iii, sp_weapon_set, r_mark, sp_weapon_times;
    object sp_weapon, weapon_room;

    if( !environment(this_object()) ) return;

    q_iii = query("iii");

    if( q_iii == 0 || q_iii == 4 )
    {
        set("sell_this_time", sell_kind[random(sizeof(sell_kind))]);
        switch( query("sell_this_time") )
        {
            case "������": list_temp=can_sell_weapon; break;
            case "��Ʒ��": list_temp=can_sell_other; break;
            case "����": list_temp=can_sell_tools; break;
            case "����": list_temp=can_sell_quest; break;
            default:list_temp=can_sell_other;
        }
    }

// ��������λ�����ر�Ĳ���
// �ؽ����������б�ǵĽ� n �ѣ���������ص��ڡ��� n �ѽ���ͬ�����ֵģ�
// �õ�����һ�ѣ����ܹ������� JOB��
// �����鱦�ͣ������б�ǵ�ˮ���������ࣩn �ţ�ԭ��ͬ��

    if( q_iii == 5 ) sp_weapon_set = random( 9 );
    if( q_iii == 6 ) sp_weapon_set = 9 + random( 7 );

// ������
    if( q_iii == 5 || q_iii == 6 )
    {
        sp_weapon_times = 1;
        while( sp_weapon_times -- )
        {
            sp_weapon = new( __DIR__"hj_obj_weapon" );
            sp_weapon->setme( sp_weapon_set );
            sp_weapon->set("cj-sheng.zb-ke", this_object() );
            r_mark = 1 + random( HJ_ROOM_AMOUNT );
            weapon_room = find_object( HJ_DIR + "hj_room" + r_mark );
            if( !weapon_room )
                weapon_room = load_object( HJ_DIR + "hj_room" + r_mark );
            sp_weapon->move( weapon_room );
            set("finding_name", delcolor( sp_weapon->query("name") ) );
        }
    }

    if( q_iii == 5 )
    {
        set("found_sword", "no");
        set("found_all_sword", "no");
    }
    if( q_iii == 6 )
    {
        set("found_crystal", "no");
        set("found_all_crystal", "no");
    }

    set("job_set_finish", 1);
    call_out("random_move", 1);
    call_out("delete_me", del_me_time[  q_iii  ] + random(120) );
}

int random_move()
{
    string *dirs;

    if(query("cannot_rdmove")) return 0;

    dirs=({
"east","west","south","north","northeast","northwest","southeast","southwest"
        });

    if(random(5) == 1 && living(this_object()))
        command(dirs[random(sizeof(dirs))]);

    remove_call_out("random_move");
    call_out("random_move",5,this_object());
    return 1;
}

#include "hj_npc_quest_action.h"
