//                ��׼��������ʾ��                                   |
// ����ת�� �þ���Ϸ�� EXP POT �ķ���
// by naihe  2002-11-09  ��ï��

#include <ansi.h>
inherit ROOM;
#include <ctime_format_func.h>

#include "z_hj_log_func.h"
// ���ļ��ж�����LOG�ļ����ļ�����HJ1_LOG_FILE
// �Լ� hj_log_file(string log_msg) ������
// ���ļ��� ��Ϸ���ڴ� ��ʹ�� hj_log_file() ����������ֱ��ʹ�� log_file() .

void create()
{
    set("short", "�þ���Ϸ��Ʒת�ô�");
    set("long", "
    �þ���Ϸ��һ��û��EXP��û��SKILLSҪ�����Ϸ�����˿��棬
����Ч��һ��������Ҫ���ǣ������������Լ�����ID����ʱ��ʹ��
һ�����ID����������ע���ID����������Ϸ�����ң�

       "HIR"��Ϸ�õ��ľ���ֵ��Ǳ��ֵ����ת�ø��Ǽǵ�ID"NOR"

    ������ID���Ǽ�һ�Σ������໥ת������Ϸ��õ��� EXP/POT ��
    "HIG"<dengji ����ID>"NOR"   �Ǽ�����໥ID(��ID�����׸��Ǽ�һ��)
    "HIG"<checkme>"NOR"         ��ѯ�Լ���δת���� EXP/POT ���
    "HIG"<take exp / pot ����>"NOR"  �� EXP/POT ����
    "HIG"<zhuan exp / pot ����>"NOR" �� EXP/POT ת���Ǽ�ID��ͬʱ����

    ����ϸ��˵����������<help here> ָ�\n\n");
    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("valid_startroom", 1);

    set("exits", ([
        "down":__DIR__"room_door_hj",
        ]));

    setup();
}

void init()
{
    add_action("do_zhuan","zhuan");
    add_action("do_take", "take");
    add_action("do_checkme","checkme");
    add_action("do_dengji","dengji");
    add_action("do_help","help");
}

int do_help(string arg)
{
    string msg;
    if(!arg || arg!="here") return 0;

    msg = "###########  �þ���Ϸ�Ǽ�ID��ϸ˵�� #############
    Ϊ�˷�ֹ���֡��ڶ�������һ������ID���������
��ʵ�С��໥�Ǽǡ��Ĺ����������ֻ��Ҫ���κ�
����ID���Ǽ��϶Է���ID���Ϳ�����ɵǼ�����������
���������κ�ʱ������������һ��ID������Ϸ������
�õ��ľ���ֵ��Ǳ��ֵ��������ת�ø���һ��ID��������

    ��ϣ���ܹ���������ID�ĵ����໥ת�ã�
    \"naihe\" ----> ��ID  \"money\" ----> ����ID\n";

    msg += "
    ��ô��������\"naihe\"����ָ�<dengji money>��
����\"money\"����ָ�<dengji naihe>��������ɡ�
����Ժ����պ������Ϸʱ��������\"naihe\"����
\"money\"���õ��ľ��顢Ǳ�ܽ��������������໥֮��
����ת���ˡ�

    ף��Ϸ��죡
                           by naihe 2003-10-22
#################################################\n";

    this_player()->start_more( msg );
    return 1;
}

int do_dengji(string arg)
{
    object me = this_player();

    if( me->query( "huanjing2003/together_id" ) )
        return notify_fail("���Ѿ��Ǽǹ�����໥ID�ˣ������� <checkme> ָ��鿴��\n������ģ����� <mto> ָ����ż�����ϵ��ʦ�κ�(naihe)��\n");
    if(!arg) return notify_fail("�㻹δ�Ǽ�����໥ID��������һ��ID����ע�⣬�ǼǺ��㲻���ٴθ������ID��\n���в�����֮���������� <help here> ��ѯ��\n");
    if( arg == me->query("id") ) return notify_fail("���صǼ��Լ�����ֱ��ת�á�\n");

    me->set("huanjing2003/together_id", arg );

    write("�Ǽǳɹ������ \""+arg+"\" δ�Ǽ�������ID����Ǽ����������޷��໥ת�á�\n");
    return 1;
}

int do_take( string arg )
{
    object me = this_player();
    int amount;
    string type;

    if(!arg) return notify_fail("ָ�����ȷ��ʽ������ <look> �鿴��\n");

    if( sscanf(arg, "exp %d", amount) )
        type = "exp";
    if( type != "exp" && sscanf(arg, "pot %d", amount) )
        type = "pot";

    if( type != "exp" && type != "pot" )
        return notify_fail("ָ�����ȷ��ʽ������ <look> �鿴��\n");

    if(amount < 1 || !me->query("huanjing2003/" + type )
      || me->query("huanjing2003/" + type ) < amount )
        return notify_fail("��û���㹻�� "+type+" ���Զ��ֻ���ֵ����ȷ��������<checkme>��ѯ��\n");

    if( type == "exp" )
    {
        if( amount < 1000 )
            return notify_fail("EXP ���֣�ÿ������ 1000 �㡣\n");
        me->add("huanjing2003/exp",-amount);
        me->add("combat_exp",amount);
    }
    if( type == "pot" )
    {
        if( amount < 500 )
            return notify_fail("POT �Ķ��֣�ÿ������ 500 �㡣\n");
        me->add("huanjing2003/pot", -amount);
        me->add("potential", amount);
    }

    message_vision( sprintf("$N�� %d ��þ���Ϸ������ %s ���ֳ���MUD��� %s ��\n", amount, type, type), me );

    hj_log_file( sprintf("\n%s(%s)������ %d ��þ� %s ��(%s)\n",
        me->query("name"), getuid(me), amount, type, ctime_format() ));
    return 1;
}


int do_zhuan(string arg)
{
    object me=this_player(),target;
    int amount;
    string target_id, type = ".";

    // ���۸�ʽ��ȷ����ȸ���ʾ��
    target_id = me->query("huanjing2003/together_id");
    if( !target_id ) return notify_fail("�㲢δ�Ǽ�����໥ID��\n");

    target = find_player( target_id );
    if( !target )
        return notify_fail("�����Ǽǵ�ID \""+target_id+"\" �������ߣ�����ת�á�\n");
    if( target->query("huanjing2003/together_id") != getuid(me) )
        return notify_fail("�����Ǽǵ�ID \""+target_id+"\" ���Է���û�еǼ����ID������ת�á�\n");

    // ok.
    if(!arg) return notify_fail("ָ�����ȷ��ʽ������ <look> �鿴��\n");

    if( sscanf(arg, "exp %d", amount) )
        type = "exp";
    if( type != "exp" && sscanf(arg, "pot %d", amount) )
        type = "pot";

    if( type != "exp" && type != "pot" )
        return notify_fail("ָ�����ȷ��ʽ������ <look> �鿴��\n");

    if(amount < 1 || !me->query("huanjing2003/" + type )
      || me->query("huanjing2003/" + type ) < amount )
        return notify_fail("��û���㹻�� "+type+" ����ת�û���ֵ����ȷ��������<checkme>��ѯ��\n");

    if( type == "exp" )
    {
        if( amount < 1000 )
            return notify_fail("EXP ��ת��ÿ������ 1000 �㡣\n");
        me->add("huanjing2003/exp",-amount);
        target->add("combat_exp",amount);
    }
    if( type == "pot" )
    {
        if( amount < 500 )
            return notify_fail("POT ��ת��ÿ������ 500 �㡣\n");
        me->add("huanjing2003/pot", -amount);
        target->add("potential", amount);
    }

    message_vision( sprintf("$N�� %d ��þ���Ϸ������ %s ת����$n��\n",amount,type ),
        me, target );

    hj_log_file( sprintf("\n%s(%s)ת�� %d ��þ� %s �� %s(%s) ��(%s)\n",
        me->query("name"), getuid(me), amount, type,
        target->query("name"),getuid(target),ctime_format() ));

    return 1;
}


int do_checkme()
{
    object me=this_player();

    if( me->query("huanjing2003/exp") > 0 )
        write(HIY"���� "+me->query("huanjing2003/exp")+" ���ڱ���Ϸ���õľ���ֵ��\n"NOR);
    else write(HIY"��û���ڱ���Ϸ���õľ���ֵ��\n"NOR);

    if( me->query("huanjing2003/pot") > 0 )
        write(HIY"���� "+me->query("huanjing2003/pot")+" ���ڱ���Ϸ���õ�Ǳ��ֵ��\n"NOR);
    else write(HIY"��û���ڱ���Ϸ���õ�Ǳ��ֵ��\n"NOR);

    write("�����ֱ�Ӱ����Ƕһ�����ľ���ֵ��Ǳ��ֵ�����߰�����ת�������Ǽǵ��໥ID��\n");

    if( me->query("huanjing2003/together_id") )
        write("��Ǽǵ��໥ID�ǣ�\""+me->query("huanjing2003/together_id")+"\"\n");
    else write("�㻹δ�Ǽ��໥ID������ת����Щ�÷֡���Ҫת��ʱ�����ȵǼǡ�\n");

    return 1;
}

