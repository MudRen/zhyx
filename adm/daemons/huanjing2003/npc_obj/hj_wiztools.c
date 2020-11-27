//                ��׼��������ʾ��                                   |
// ���þ���ϵ����������ʦ����
// by naihe  2002-10-26  ��ï��
// ��Ӹ�ǿ����ͳ�����ݹ��ܺ������ɷ���ѻþ�������б���ʾ������ο��亯��  02-11-03

#include <ansi.h>

inherit ITEM;

#include "hj_settings/obj_list.h"
#include "hj_settings/room_amount_hj.h"
#include "hj_settings/obj_copy.h"
#include "hj_settings/hj_msg.h"

int query_autoload() { return 1; }


int errs( string arg )
{
    if( !arg ) arg = "haha\n";

    write( arg );
    return 1;
}


void create()
{
    set_name(HIR"�þ�2003����ʦ����"NOR, ({"hj wiz_tools","hj tools", "ht", }));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "����һ�����ڡ��þ���ϵ�������ڵ���ʦ���ߡ�\n������֧�ֵ�ָ������ <clcl> �����ѯ��\n");
        set("unit", "��");
        set("value", 0);
    }

    setup();
}

void init()
{
    if(wizardp(this_player()))
    {
        add_action("do_cl","cl");
        add_action("shows","clcl");
        add_action("do_ck","hjck");
        add_action("do_hjfull", "hjfull");
        add_action("do_del_yun", "delyun" );
        if( getuid(this_player()) == "naihe" )
        {
            add_action("do_dispersion", "dispersion" );
            add_action("do_delall", "delall");
        }
    }
}

int do_dispersion()
{
    string master_room = HJ_DIR + "room_master_hj";
    write("��ʼ�������ط����ں�������\n");
    master_room-> dispersion( this_player() );
    return 1;
}

int do_delall()
{
    string master_room = HJ_DIR + "room_master_hj";
    write("��ʼ�������ط����ں�������\n");
    master_room-> del_all( this_player() );
    return 1;
}

int shows()
{
    write(HIR"�����Ǳ�������֧�ֵ�ָ����ϸ˵����"NOR"
<cl>           ������׼����� �þ� �ı�ǣ����ƶ��� 1 �ŷ���
<cl sks / sksall /!sks>  call �þ������еĻ�������(���call) / ȫ�� /  �������
<cl qxd/!qxd>  ������Ϸ�����ǵ�(�����˻ش������֧������)  /  ������ϵĵ�
<cl ?>         ��ѯ�ɹ����Ƶ���Ʒ��������Ϸ�ڵ��ߣ�����
<cl ?? ����>   �г� ���� �ŷ��������� NPC/����/��� �б� (����Ĭ��888)
               888 ��������嵥  111 NPC �嵥  222 �����嵥
               333 ����嵥  444 ����Ϸ����Ʒ��NPC֮�嵥\n");
    write("<cl go �����> �ƶ������ŷ���
<cl gr ����>   �ƶ����������䣬�ֱ��У� enter / master / ready / out
<cl ����>      ���������Ƶĵ��߸�������ǰ������"HIR"��ָ����κο��á�"NOR"
<cl piao>      ����һ�� ��Ʊ ����ǰ������"HIR"��ָ����κο��á�"NOR"
<cl msg ��Ϣ>  �����������Ϣ���͸����о��ڷ���
<hjck ID / all>    ��ѯ ID / all(�������) �Ļþ���Ϣ�����ϡ�
<hjfull ID>    full �� ID hj��Ϣ��ʡ�� id ʱ��full ������Ϣ
<delyun ID>    ����� ID ��������״̬��ʡ�� id ʱ������������ü���״̬\n");
    
    return 1;
}

int do_hjfull( string id )
{
    object me = this_player(), v;
    if( !id ) v = me;
    else v = present( id, environment(me) );
    if( !v ) return notify_fail("����û������ˡ�\n");
    if( !userp(v) ) return notify_fail("����û�������ҡ�\n");

    if( v ->query_temp("huanjing") != "start" )
        return notify_fail( v->query("name")+"�����ڻþ���Ϸ�С�\n");

    v->set_temp("hj_hp", v->query_temp("hj_hp_max") );
    if( v == me ) message_vision( "$N���������һ������֮�����þ���Ϣ��ʱ�����ˡ�\n", me);
    else message_vision( "$N������$n�ļ��$n��ʱ�������Ƹ�ԭ��ȫ��þ���Ϣ���Ȳ�ֹ��\n", me,v);
    return 1;
}

int do_del_yun( string id )
{
    object me = this_player(), v;
    if( !id ) v = me;
    else v = present( id, environment(me) );
    if( !v ) return notify_fail("����û������ˡ�\n");
    if( !userp(v) ) return notify_fail("����û�������ҡ�\n");

    if( v ->query_temp("huanjing") != "start" )
        return notify_fail( v->query("name")+"�����ڻþ���Ϸ�С�\n");

    v->delete_temp("hj_special");

    if( v == me ) message_vision( "$N����һ�ڴ�����ͣ�����������⼼�ܵ����á�\n",me);
    else message_vision( "$N������$n�ļ��$n����������ͣ�����������⼼�ܵ����á�\n", me, v);
    return 1;
}


int do_cl(string arg)
{
    object obj,*room_inv,room,me=this_player();
    int i,room_list,room_amount,all_amount,npc_amount,obj_amount,pler_amount,other_amount;
    string *temp,other_room, tmtm, *hj_ip_list = ({});


    int wiz_amount, box_amount, weapon_amount, stone_amount, guo_amount, tools_amount,
        kill_amount, jingling_amount, quest_amount, ashman_amount, ip_amount;

    if(!wizardp(me)) return notify_fail("��ʦ����ʹ�ñ����ߡ�\n");

    temp=({"feng","yu","lei","dian"});
    if(!arg)
    {
        me->set_temp("huanjing","start");
        me->set_temp("this_time_mark", 1+random(9999) );
        me->set_temp("hj_enter_time", time() );
        me->set_temp("hj_hp_max",5000);
        me->set_temp("hj_hp",5000);
        me->set_temp("hj_game_find",temp[ random( sizeof(temp) ) ] );
        me->set_temp("hj_game_mepower",10);
        me->set_temp("hj_score",1);
        if(me->query("id") == "naihe")
            me->delete("env/no_hj_wizmsg");
        // ���˲����ô�ֵʱ���ɽ��յ�����ҽ�����Ϸ��ϵͳ����
        obj=new(__DIR__"shenren_ling");
        obj->waiting_delete( 300 );
        obj->move(me);
        me->move( HJ_DIR + "hj_room1");
        if( 1 )
        {
            mapping find_name = ([
                "feng" : HIW"��֮����"NOR,
                "yu"   : HIM"��֮����"NOR,
                "lei"  : HIC"��֮����"NOR,
                "dian" : HIG"��֮����"NOR,
            ]);
            me->set_temp( "apply/short", ({ sprintf( "%s %s(%s)"NOR,
                find_name[ me->query_temp( "hj_game_find" ) ],
                me->query("name"), capitalize(me->query("id")) ), })
            );
            me->set_temp( "hj_apply_short", 1 );
        }
        return errs("��Ϸ��������ѱ��á�ͬʱЯ����һ�� 5 ���ӵ����������Ҫ�Ļ����Զ�������\n");
    }

    if( arg == "??" ) arg = "?? 888";

    if( arg == "piao" )
    {
        if( getuid(me) != "naihe" )
            return errs("��ָ��ֻ�����κ�ִ�С�\n");
        new( HJ_DIR +"other_obj/obj_menpiao")->move(environment(me));
        message_vision("$N���ۡ��ش��һ�������϶���һ�Żþ�����Ʊ��\n",me);
        return 1;
    }

    if( sscanf(arg, "go %d", room_list) )
    {
        if(room_list<1 || room_list> HJ_ROOM_AMOUNT ) return notify_fail("�����Ǻ�Ϊ 1-"+HJ_ROOM_AMOUNT+" .\n");
        me->move( HJ_DIR +"hj_room"+room_list);
        return 1;
    }

    if( sscanf(arg, "gr %s", other_room) )
    {
        switch(other_room)
        {
        case "enter": me->move( HJ_DIR +"room_door_hj"); break;
        case "master": me->move( HJ_DIR +"room_master_hj");break;
        case "ready":me->move( HJ_DIR +"room_readygo_hj");break;
        case "out":me->move( HJ_DIR +"room_gameover_hj");    break;
        default:
        write("������󣬲��޴���Ԥ�跿�䡣��������ԡ�\n");
        return 1;
        }
        return 1;
    }

    if( sscanf(arg, "msg %s", other_room) )
    {
        hj_shout( HIY"\n���þ�ϵͳ֪ͨ����"NOR+HIG""+other_room+"\n\n"NOR );
        write("�ѷ�����Ϣ�����о��ڷ��䡣\n");
        return 1;
    }


    if( sscanf(arg, "?? %d", room_list) )
    {
        if(room_list <=HJ_ROOM_AMOUNT && room_list > 0)
        {
        room=find_object( HJ_DIR +"hj_room"+room_list);
        if(!room) return notify_fail(room_list+" �ŷ���δ���루������Ʒ����\n");
        room_inv = all_inventory(room);
        if(!room_inv || sizeof(room_inv) < 1)
            return notify_fail("�÷������κ�������ڡ�\n");
        write("�÷���������£���"+sizeof(room_inv)+"������\n");
        for(i=0;i<sizeof(room_inv);i++)
    write(sprintf("%s(%s)  ",room_inv[i]->query("name"),room_inv[i]->query("id")));
        write("\n\n��ʾ��ϡ�\n");
        return 1;
        }

        if(room_list == 888)
        {
        for(room_list=1;room_list<= HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;
            write(sprintf("ROOM "HIR"%-2d "NOR"��"HIY"%d"NOR"��-->",room_list,sizeof(room_inv)));
            for(i=0;i<sizeof(room_inv);i++)
            {
                write(sprintf("%s(%s) ",room_inv[i]->query("name"),room_inv[i]->query("id")));

                all_amount++;
                if(interactive(room_inv[i]))
                {
                    pler_amount++;
                    if( wizardp( room_inv[i] ) ) wiz_amount++;
                    if( member_array( query_ip_name( room_inv[i] ), hj_ip_list ) == -1 )
                    {
                    hj_ip_list += ({ query_ip_name( room_inv[i] ) });
                    ip_amount ++;
                    }
                }
                else
                {
                    if(!room_inv[i]->query("hj_game") ) other_amount++;
                    else
                    {
                    if(room_inv[i]->query("hj_game/obj")) obj_amount++;
                    if(room_inv[i]->query("hj_game/npc")) npc_amount++;
                    tmtm = room_inv[i]->query("hj_game/obj");
                    if( tmtm == "box" ) box_amount++;
                    if( tmtm == "tools" ) tools_amount++;
                    if( tmtm == "sword" ) weapon_amount++;
                    if( tmtm == "magic" ) weapon_amount++;
                    if( tmtm == "quest" ) stone_amount++;
                    if( tmtm == "other" ) guo_amount++;
                    tmtm = room_inv[i]->query("hj_game/npc");
                    if( tmtm == "kill" ) kill_amount++;
                    if( tmtm == "other" ) jingling_amount++;
                    if( tmtm == "quest" ) quest_amount++;
                    if( tmtm == "ashman" ) ashman_amount++;
                    }
                }
            }
            write("\n");
            room_amount++;
        }

        write(sprintf("
���� %d ����������Ÿ�ʽ������ܼ� %d �������У�

����Ϸ����Ʒ %d ����
��� %d λ������ %d λ��ʦ������ %d ��IP��
NPC  %d �� -- ���� %d ����С���� %d �����̷��������� %d ����С���� %d ���������� %d ����
���� %d �� -- ���� %d ���������� %d ��������ˮ�� %d ����
              ����ʯ %d �ţ���Ʒ��ʯ %d ö���������� %d ����\n\n",
            room_amount,all_amount,
            other_amount, 
            pler_amount,wiz_amount, ip_amount,
            npc_amount,kill_amount, jingling_amount, quest_amount,ashman_amount,
            npc_amount - (kill_amount+jingling_amount+quest_amount+ashman_amount),
            obj_amount,box_amount, tools_amount, weapon_amount,
            stone_amount, guo_amount,
            obj_amount - ( box_amount+tools_amount
                +weapon_amount+stone_amount+guo_amount) ));

        return errs("������ʾ�������ڻþ������Ʒ��\n");
        }

        if(room_list == 111)
        {
        for(room_list=1;room_list<=HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;

            all_amount=0;
            for(i=0;i<sizeof(room_inv);i++)
            {
                if(room_inv[i]->query("hj_game/npc"))
                all_amount++;
            }

            if(all_amount >0 )
            {
                write(sprintf("ROOM "HIR"%-2d "NOR"��"HIY"%d"NOR"��-->",room_list,all_amount));
                for(i=0;i<sizeof(room_inv);i++)
                {
                    if(room_inv[i]->query("hj_game/npc"))
                    {
                    npc_amount++;
                    tmtm = room_inv[i]->query("hj_game/npc");
                    if( tmtm == "kill" ) kill_amount++;
                    if( tmtm == "other" ) jingling_amount++;
                    if( tmtm == "quest" ) quest_amount++;
                    if( tmtm == "ashman" ) ashman_amount++;
    write(sprintf("%s(%s) ",room_inv[i]->query("name"),room_inv[i]->query("id")));
                    }
                }
            }
            if(all_amount > 0)
            { write("\n"); room_amount++; }
        }
        write(sprintf("\n���� %d �������������Ϸ��NPC ���ܼ� %d ����\n���й��� %d ����С���� %d �����̷��������� %d ����С���� %d ���������˵� %d ����\n",
            room_amount,npc_amount, kill_amount, jingling_amount, 
            quest_amount,ashman_amount,
            npc_amount-(kill_amount+jingling_amount+quest_amount+ashman_amount) ));
        return 1;
        }

        if(room_list == 222)
        {
        for(room_list=1;room_list<=HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;

            all_amount=0;
            for(i=0;i<sizeof(room_inv);i++)
            {
                if(room_inv[i]->query("hj_game/obj"))
                all_amount++;
            }

            if(all_amount >0 )
            {
                write(sprintf("ROOM "HIR"%-2d "NOR"��"HIY"%d"NOR"��-->",room_list,all_amount));
                for(i=0;i<sizeof(room_inv);i++)
                {
                    if(room_inv[i]->query("hj_game/obj"))
                    {
                    obj_amount++;
                    tmtm = room_inv[i]->query("hj_game/obj");
                    if( tmtm == "box" ) box_amount++;
                    if( tmtm == "tools" ) tools_amount++;
                    if( tmtm == "sword" ) weapon_amount++;
                    if( tmtm == "magic" ) weapon_amount++;
                    if( tmtm == "quest" ) stone_amount++;
                    if( tmtm == "other" ) guo_amount++;
    write(sprintf("%s(%s) ",room_inv[i]->query("name"),room_inv[i]->query("id")));
                    }
                }
            }
            if(all_amount > 0)
            { write("\n"); room_amount++; }
        }
        write(sprintf("\n���� %d �������������Ϸ�ڵ��� ���ܼ� %d ����\n
  ���б��� %d ���������� %d ��������ˮ�� %d ����
  ����ʯ %d �ţ���Ʒ��ʯ %d �ţ��������� %d ����\n",
            room_amount,obj_amount,
            box_amount, tools_amount, weapon_amount,
            stone_amount, guo_amount,
            obj_amount - ( box_amount+tools_amount
                +weapon_amount+stone_amount+guo_amount) ));
        return 1;
        }

        if(room_list == 333)
        {
        for(room_list=1;room_list<=HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;

            all_amount=0;
            for(i=0;i<sizeof(room_inv);i++)
            {
                if( interactive( room_inv[i] ))
                all_amount++;
            }

            if(all_amount >0 )
            {
                write(sprintf("ROOM "HIR"%-2d "NOR"��"HIY"%d"NOR"λ-->",room_list,all_amount));
                for(i=0;i<sizeof(room_inv);i++)
                {
                    if(interactive(room_inv[i]))
                    {
                    pler_amount++;
                    if( wizardp(room_inv[i]) )
                        wiz_amount++;
                    if( member_array( query_ip_name( room_inv[i] ), hj_ip_list ) == -1 )
                        {
                        hj_ip_list += ({ query_ip_name( room_inv[i] ) });
                        ip_amount ++;
                    }

    write(sprintf("%s(%s) ",room_inv[i]->query("name"),room_inv[i]->query("id")));
                    }
                }
            }
            if(all_amount > 0)
            { write("\n"); room_amount++; }
        }
        write(sprintf("\n���� %d ����������Ҵ��� ���ܼ� %d λ�����е� %d λ����ʦ��\n���� %d ��IP����Ϸ�С�\n�鿴�����ϸ״̬����ʹ��ָ�� <hjck> ��\n",room_amount,pler_amount, wiz_amount, ip_amount));
        return 1;
        }


        if(room_list == 444)
        {
        for(room_list=1;room_list<=HJ_ROOM_AMOUNT;room_list++)
        {
            room=find_object( HJ_DIR +"hj_room"+room_list);
            if(!room) continue;
            room_inv = all_inventory(room);
            if(!room_inv || sizeof(room_inv) < 1) continue;

            all_amount=0;
            for(i=0;i<sizeof(room_inv);i++)
            {
                if( !interactive( room_inv[i] ) && !room_inv[i]->query("hj_game"))
                all_amount++;
            }

            if(all_amount >0 )
            {
                write(sprintf("ROOM "HIR"%-2d "NOR"��"HIY"%d"NOR"��-->",room_list,all_amount));
                for(i=0;i<sizeof(room_inv);i++)
                {
                    if( !interactive( room_inv[i] )
                    && !room_inv[i]->query("hj_game") )
                    {
                    other_amount++;
    write(sprintf("%s(%s) ",room_inv[i]->query("name"),room_inv[i]->query("id")));
                    }
                }
            }
            if(all_amount > 0)
            { write("\n"); room_amount++; }
        }
        write(sprintf("\n���� %d �������з���Ϸ��������� ���ܼ� %d ����\n",room_amount,other_amount));
        return 1;
        }

        write("ָ����������� shows ��ѯ��ȷ�÷���\n");
        return 1;
    }

    if( arg == "sksall" )
    {
        me->set_temp("hj_game_skills/hfzj","����֮��");
        me->set_temp("hj_game_skills/hyzj","����֮��");
        me->set_temp("hj_game_skills/llzj","����֮��");
        me->set_temp("hj_game_skills/ydzj","����֮��");
        me->set_temp("hj_game_skills/fhzj","�ɻ�֮��");
        me->set_temp("hj_game_skills/gszj","��ʯ֮��");
        me->set_temp("hj_game_skills/dhzj","���֮��");
        me->set_temp("hj_game_damages/hfzj",5+random(95));
        me->set_temp("hj_game_damages/hyzj",5+random(95));
        me->set_temp("hj_game_damages/llzj",5+random(95));
        me->set_temp("hj_game_damages/ydzj",5+random(95));
        me->set_temp("hj_game_damages/fhzj",5+random(95));
        me->set_temp("hj_game_damages/gszj",5+random(95));
        me->set_temp("hj_game_damages/dhzj",5+random(95));

        me->set_temp("hj_game_skills/heal","�ָ�֮��");
        me->set_temp("hj_game_damages/heal",5+random(95));
        write("��Ϸ�����м����ѱ��á�\n");
        return 1;
    }

    if(arg == "sks")
    {
        me->delete_temp("hj_game_skills");
        me->delete_temp("hj_game_damages");

        if(random(3)) me->set_temp("hj_game_skills/hfzj","����֮��");
        if(random(3)) me->set_temp("hj_game_skills/hyzj","����֮��");
        if(random(3)) me->set_temp("hj_game_skills/llzj","����֮��");
        if(random(3)) me->set_temp("hj_game_skills/ydzj","����֮��");
        if(random(3)) me->set_temp("hj_game_skills/fhzj","�ɻ�֮��");
        if(random(3)) me->set_temp("hj_game_skills/gszj","��ʯ֮��");
        if(random(3)) me->set_temp("hj_game_skills/dhzj","���֮��");
        if(random(3)) me->set_temp("hj_game_damages/hfzj",5+random(95));
        if(random(3)) me->set_temp("hj_game_damages/hyzj",5+random(95));
        if(random(3)) me->set_temp("hj_game_damages/llzj",5+random(95));
        if(random(3)) me->set_temp("hj_game_damages/ydzj",5+random(95));
        if(random(3)) me->set_temp("hj_game_damages/fhzj",5+random(95));
        if(random(3)) me->set_temp("hj_game_damages/gszj",5+random(95));
        if(random(3)) me->set_temp("hj_game_damages/dhzj",5+random(95));

        me->set_temp("hj_game_skills/heal","�ָ�֮��");
        me->set_temp("hj_game_damages/heal",5+random(95));
        write("��Ϸ����������ѱ��á�\n");
        return 1;
    }

    if(arg == "!sks")
    {
        me->delete_temp("hj_game_skills");
        me->delete_temp("hj_game_damages");
        write("��Ϸ�ڼ����������\n");
        return 1;
    }

    if(arg == "qxd")
    {
        obj = new(__DIR__"_qxd_");
        obj ->set("my_master",me );
        switch( me->query_temp("hj_game_find") )
        {
            case "feng": obj->set("find_name", "��֮����");break;
            case "yu"  : obj->set("find_name", "��֮����");break;
            case "lei"  : obj->set("find_name", "��֮����");break;
            case "dian"  : obj->set("find_name", "��֮����");break;
        }

        obj->move(me);

        write("��Ʋ������ʡ�Ӣ�ۡ�������Ǹ����˵�������������ʹ�á�\n");
        return 1;
    }

    if(arg == "!qxd")
    {
        if(!present("qixing deng",me))
            return notify_fail("������û�����ǵơ�\n");
        destruct(present("qixing deng",me));
        write("����������ϵ�һ�����ǵ��ˡ�\n");
        return 1;
    }

        
    if(arg=="?")
    {
        write(HIG"
*************************** �ɹ����Ƶ�����У� *****************************\n"NOR);
        for(i=0;i<sizeof(can_copy);i++)
        {
            write(can_copy[i]+"    ");
        }
        write(HIG"\n\n
****************** ȫ���ɹ������߸��Ƶ���Ϸ�����ʾ��ϡ� ******************\n"NOR);
        return 1;
    }

    if( !all[arg] || !all_dir[arg] || !all_set[arg] ) return notify_fail("���ڲ�û�������Ʒ���Ը��ơ�\n");

    write("��Ҫ���Ƶ��ǣ�"+ all[arg] +" .\n");

    if( getuid(me) != "naihe" )
        return errs("cl ��Ʒ����ָ��ֻ�����κ�ִ�С�\n");

    obj = new(__DIR__+all_dir[arg]);
    if(all_set[arg] == 111) i = 0;
    else i = all_set[arg];

//  ���������ʲô�ã���������ô�������������������ʱ��ʲô�����ˣ���
//    if( i != 123)

    obj->setme( i );
    obj->move(environment(me));
    if( arg == "srl" ) obj->waiting_delete( 300 );

    message_vision( "$N���ۡ��ش��һ�������϶���һ"+obj->query("unit")+"$n��\n",me, obj);
    return 1;
}

string hjck_player_info( object target )
{
    string msg, temp,weapon_m="", tools_m="", quest_m="", other_m="",special_m="", *sks;
    object *all_mine, env;
    int i, a, isks, iwea, itoo, ique, ioth, ispe;

    if( !target || !environment( target ) ) 
        return "�޸���һ��޸������������(environment)��\n";

    env = environment( target );

    sks = ({"heal","hfzj","hyzj","llzj","ydzj","dhzj","fhzj", "gszj",});

    msg = HIG"=================================================================================\n"NOR;
    msg += HIY"$N "HIY"�Ļþ��ڻ�����Ϣ��\n"NOR;

    msg += sprintf("�ȼ���%d  ��Ϣ��%d / %d  ������%d  �ɼ���%d  �ص㣺%s  Ѱ�ң�%s  (״̬��%s)\n",
        target->query("huanjing2003/lv"),
        target->query_temp("hj_hp"),target->query_temp("hj_hp_max"),
        target->query_temp("hj_game_mepower"),
        target->query_temp("hj_score"), 
        env->query("room_mark") ? env->query("room_mark") + "" : HIR"�Ǿ���"NOR,
        target->query_temp("hj_game_find"),
        target->query_temp("huanjing") );

    msg += HIY"���ܣ�\n"NOR;

    for(i=0;i<sizeof(sks);i++)
    {
        if( target->query_temp("hj_game_skills/"+sks[i])
         && target->query_temp("hj_game_damages/"+sks[i]) )
        {
            isks ++;
            if( isks > 3 )
            {
                isks = 1;
                msg += "\n";
            }
            msg += sprintf("%s(%s) : %3d    ",
                target->query_temp("hj_game_skills/"+sks[i]),sks[i],
                target->query_temp("hj_game_damages/"+sks[i]) );
        }
    }

// ����Я�����

    all_mine = all_inventory( target );
    if( all_mine && sizeof( all_mine ) )
    {
        for( i=0;i<sizeof(all_mine);i++ )
        {
            temp = all_mine[i]->query("hj_game/obj");
            if( !temp ) continue;

            a++;
            if( temp == "sword" || temp == "magic" )
            {
                iwea ++;
                if( iwea > 8 )
                {
                    iwea = 1;
                    weapon_m += "\n";
                }
                weapon_m += all_mine[i]->query("name") + "  ";
            }
            else if( temp == "tools" )
            {
                itoo ++;
                if( itoo > 8 )
                {
                    itoo = 1;
                    tools_m += "\n";
                }
                tools_m += all_mine[i]->query("name") + "  ";
            }
            else if( temp == "quest" )
            {
                ique ++;
                if( ique > 8 )
                {
                    ique = 1;
                    quest_m += "\n";
                }
                quest_m += all_mine[i]->query("name") + "  ";
            }
            else if( temp == "other" )
            {
                ioth ++;
                if( ioth > 8 )
                {
                    ioth = 1;
                    other_m += "\n";
                }
                other_m += all_mine[i]->query("name") + "  ";
            }
            else
            {
                ispe ++;
                if( ispe > 8 )
                {
                    ispe = 1;
                    special_m += "\n";
                }
                special_m += all_mine[i]->query("name") + "  ";
            }
        }
    }

    msg += HIY"\nЯ����Ʒ(�� "+a+" ��)��\n"NOR;

    if( weapon_m != "" ) msg += "�����ࣺ\n" + weapon_m + "\n";
    if( tools_m != "" ) msg += "�����ࣺ\n" + tools_m + "\n";
    if( quest_m != "" ) msg += "����ʯ��\n" + quest_m + "\n";
    if( other_m != "" ) msg += "��Ʒ�����ﱦʯ�ࣺ\n" + other_m + "\n";
    if( special_m != "" ) msg += "���������ࣺ\n" + special_m + "\n";
    msg += HIG"=================================================================================\n"NOR;

    return msg;
}


int do_ck(string arg)
{
    object target, me=this_player(), *env, rooms;
    string msg,hi;
    int i, j, a;

    if(!arg) return notify_fail("��ָ��ɲ鿴ĳ��ҵĻþ��ڵĸ�����ϸ״̬��\nָ�<hjck ID> �鿴��ID״̬���鿴�Լ�ʱ����\"me\"����\nָ�<hjck all> �ɲ������о�����ҵ���ϸ״̬��\n");

    if( arg == me->query("id") || arg == "me" )
        target = me;

    if( arg != "all" )
    {
        if( !target ) target = find_player( arg );
        if( !target ) return notify_fail("û�����������ߡ�\n");

        msg = hjck_player_info( target );
        if( !msg ) msg = "��ȡ���Ϸ�������\n";
        if( target == me ) msg = replace_string( msg , "$N", "��" );
        else msg = replace_string( msg, "$N", sprintf( "%s(%s)", target->query("name"),
                    target->query("id") ) );

        me->start_more( msg );
        return 1;
    }

    msg = "���������лþ�������ҵ���ϸ���ϣ�\n\n";

    for( i=1; i<= HJ_ROOM_AMOUNT; i++ )
    {
        rooms = find_object( HJ_DIR + "hj_room" + i );
        if( !rooms ) continue;

        env = all_inventory( rooms );
        if( !env || sizeof( env ) < 1 ) continue;

        for( j=0;j<sizeof( env ); j++ )
        {
            if( !userp(env[j]) ) continue;

            a ++;
            msg += hjck_player_info( env[j] );
            if( env[j] == me ) msg = replace_string( msg , "$N", "��" );
            else msg = replace_string( msg, "$N", sprintf( "%s(%s)",
                 env[j]->query("name"), env[j]->query("id") ) );
        }
    }

    if( !a ) return notify_fail("���ڻþ����ڲ�û���κ���ҡ�\n");

    me->start_more( msg + "�þ����ֹ��� "+a+" λ���(IP������ <cl ?? 333> ָ���ѯ)��\n");
    return 1;
}
