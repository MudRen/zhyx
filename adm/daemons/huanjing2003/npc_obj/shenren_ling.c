//                ��׼��������ʾ��                                   |
// ������  �� �ִ������NPC���ٹ����Լ���
// by naihe  2002-10-28  ��ï��
// ����д��Ϊ�˲���ʱ�ã������룬������Ϸ��Ҳ�Ƿǳ�����˼ѽ������
// naihe 05-9-4 12:27 ǿ���ˣ������߿ɶ�����Ը������һ�й�����Ϊ��
//       ����NPC����ҹ��������𡢷�����֮��Ĺ����ȡ�

#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(HIY"��"HIM"��"HIR"��"NOR, ({"shenren ling","ling"}));
    set_weight(100);
    if (clonep())
        set_default_object(__FILE__);

    else
    {
        set("long", "����һ���������������ɢ����ʥ֮��������а��ħ�Ȳ��ҹ����㡣\n");
        set("unit", "��");
        set("value", 0);
    }

    set("hj_game/obj","shenren ling");
    setup();

    call_out("delete_me", 3 );
    // ����δ֪bug�����Ա�����ô˺��������κθ��ƴ���Ʒ�����ˣ�����Ҫ�� waiting_delete()
    // ��������ֵ��
}


// �����ط����ƴ��ļ�ʱ����������������������ɾ��ʱ�䡣
// ����������ǰ�ġ���ʦ�á��������������Σ���Ҫ����ɾ����
void waiting_delete( int del_time )
{
    if( !del_time ) del_time = 3;
    if( del_time > 600 ) del_time = 600;
    // ��� 10 ����Ҫɾ����

    set( "for_wiz_check_delete_time", del_time ); // ��ѯʱ����֪�������Ƿ����ӳ� delete ��
    remove_call_out( "delete_me" );
    call_out("delete_me", del_time );
}

void delete_me()
{
    if( !environment(this_object()) ) return;
    message_vision("$N��������ҫ�۹�â���漴��ʧ�����ˡ�\n",this_object());
    destruct(this_object());
}
