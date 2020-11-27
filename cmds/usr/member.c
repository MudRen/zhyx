/***************��Աϵͳ����ӿ�*******************************
 Create by Rcwiz for HERO 2003
************************************************************/

#include <ansi.h>
 
#define MEMBER_D         "/adm/daemons/memberd"
#define GOODS_D          "/adm/daemons/goodsd"
int paying;
int help(object me);
int help2(object me);

int main(object me, string arg)
{
          string str1, str2;
          object tar;
          string me_id, tar_id;
          int amount;

          if (time() - me->query_temp("last_member") < 5 
              && arg != "?" 
              && ! wizardp(me))
                return notify_fail("ϵͳæ�����Ժ����ԣ�\n");
          
          if (arg != "?" && ! wizardp(me))me->set_temp("last_member", time());
          
          // ������ǻ�Աʹ��member ?, member ??,member pay, member stats, member show goodsָ��
          if (! MEMBER_D->is_member(me->query("id")))
          {
                if (! arg)return 0;
                if (arg == "?")return help2(me);
                if (arg == "??")return help(me);
                if (arg == "stats")
                {
                	me->add_temp("last_member", 5);
                	return MEMBER_D->show_all_members(0);
                }
                if (sscanf(arg, "%s %s", str1, str2) != 2)
                       return 0;

                if (str1 != "pay" &&
                    (str1 != "show" || str2 != "goods") )return 0;
          }

          if (! arg)
          {
                MEMBER_D->show_member_info(me->query("id"), "info", me);
                return 1;
          }

          if (arg == "?")return help2(me);
          if (arg == "??")return help(me);
          if (arg == "stats")
          {
          	return MEMBER_D->show_all_members(0);
          }
          if (sscanf(arg, "%s %s", str1, str2) != 2)return help(me);

          switch(str1)
          {
                case "show":
                    if (str2 == "info")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "info", me);
                         return 1;
                    }
                    else if (str2 == "payinfo")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "payinfo", me);
                         return 1;
                    }
                    else if (str2 == "buyinfo")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "buyinfo", me);
                         return 1;
                    }
                    else if (str2 == "goods")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "goods", me);
                         return 1;
                    }
                    else if (str2 == "zhuaninfo")
                    {
                         MEMBER_D->show_member_info(me->query("id"), "zhuaninfo", me);
                         return 1;
                    }
                    else return help(me);

                case "pay":
                    if (paying)
                    {
                          write(HIG "ϵͳæ���Ժ����ԣ�\n" NOR);
                          return 1;
                    }
                    paying = 1; // ͬһʱ��ֻ��һ����Ա��ֵ
                    if(! MEMBER_D->pay(me, str2))
                          write("��ֵʧ�ܣ���������ע������󣬻�����Ϊ�����쳣ԭ���£�\n");
                    paying = 0;
                    return 1;

                case "buy":
                    if (! GOODS_D->buy_goods(me->query("id"), str2, me))
                    {
                          write("����ʧ�ܣ�\n");
                          return 1;
                    }
                    write("Successful!\n");
                    return 1;

                case "zhuan":
                    if (sscanf(str2, "%s:%d", tar_id, amount) != 2)return help(me);
                    me_id = me->query("id");
                    if (me_id == tar_id)return notify_fail("��׳հ������Լ�ת�ʣ�\n");

                    if (! MEMBER_D->virement_yhb(me_id, tar_id, amount, me))
                    {
                          write("ת��ʧ�ܣ�\n");
                          return 1;
                    }
                    write("Successful!\n");
                    return 1;

                case "check":
                    if (wiz_level(me) < 4)
                          return help(me);
                    
                    // ���Է��Ƿ�Ϊ��Ա
                    if (! MEMBER_D->is_member(str2))
                          return notify_fail("Ŀ��Ϊ�ǻ�Ա���޷���ѯ��\n");
                   
                    tar = UPDATE_D->global_find_player(str2);
                    if (! objectp(tar))return notify_fail("û�������ң�\n");
                    
                    MEMBER_D->show_member_info(str2, "info", tar);

                    UPDATE_D->global_destruct_player(tar, 1);

                    return 1;
     
                case "remove":
                    if (wiz_level(me) < 5)return help(me);
                             
                    if (! MEMBER_D->remove_member(str2))
                    {
                         write("ɾ����Աʧ�ܣ�\n");
                         return 1;
                    }
                    write("OK.\n");
                    return 1;

                default:     return help(me);
          }

          return 1;
}

int help (object me)
{
	write(@HELP

ָ���ʽ : member show [info | payinfo | buyinfo | zhuaninfo | goods]
           member pay ע����             ���ɻ��(��ֵ) 
           member buy ��Ʒ����           ������Ʒ
           member check id               ����Ա��Ϣ
           member stats                  �г����еĻ�Ա
           member zhuan id:amount        YHBת��
           member ??                     member ָ�����
           member ?                      �׻ƻ�Աϵͳ������

member zhuan id:amount ˵����
     1��ע���ʽ��idΪ�Է�id���Է���������Ч��Ա��
     2��amount��ת�ʽ�
     3��id��amount֮������á�:�����Ÿ�����
     4��ת�ʵı���Ҳ����Ϊ��Ч��Ա��
     5��ÿ��ת�ʽ��۳�ת�ʽ��İٷ�֮��(%3)��
�磺��ת�ʡ�1000YHB������rcwiz����ָ��Ϊ��
          
     member zhuan rcwiz:1000      ���ɡ�

info    : ��ʾ��Աϵͳ���
payinfo : ��ʾ��ʷ��ֵ������Ϣ
buyinfo : ��ʾ��ʷ������Ʒ��Ϣ
goods   : ��ʾӢ���̵���۵���Ʒ

member check id Ϊarch������ʦʹ�ò�����

��زο��ļ���help member

HELP );
        return 1;
}

int help2(object me)
{
    
    write(BBLU + HIW "                      �׻ƻ�Աϵͳ������\t              \n" NOR);
    write(HIW "---------------------------------------------------------------\n\n" NOR);
    write(HIY "����Ա���������������ֶ����ݡ����ݰ�ȫ�ԡ��ƻ��������Ӿ����Ǳ�ܡ�\n"
              "  ׬ȡ�׻ƻ��ҡ�ʹ���׻ƻ��ҹ�����Ʒ��ʹ�����µ�ת��ϵͳ�������\n"
              "  ��ϵͳ����̳����ϵͳ��������¡��Դ��书�Լ����ܱ�վ����������\n"
              "  �ݵȡ�\n\n" NOR);
    write(HIY "����γ�Ϊ��Ա����ֻ��ÿ�£�31�죩���������28Ԫ���ɻ��һ��ע��\n"
              "  �룬��ʹ�� " HIR "member pay ע����" HIY " ���ɳ�ֵ��Ϊ��Ա��������ѡ�\n\n" NOR);
    write(HIY "����ֵ���̣�\n" HIW
"**********************************************************************************************\n\n"HIG
" ����email��msg---->adminȷ��--(ͨ��)-->admin����ע����---->��ֵ--(�ɹ�)--->ϵͳ��¼��ֵ�� \n"
" ֪ͨadmin�� ��д��        ��               ������msg����               ��      Ϣ���޸���Ӧ�� \n" 
" ���ʱ�䡢ʵ�ʵ���        ��                ��                         ��      ��             \n"
" �������������     (�в��)            /                         (ʧ��)                    \n"
" Ա��ID                    ��              /                            ��                      \n"
"                    (��ʾ���ƾ֤��ʵ)--(ͨ��)                     ���Ʊ���ע���벢              \n"
"                           ��                                      ��ʱ��֪admin                 \n"
"                    (���ܳ�ʾ��Чƾ֤)                                  ��                      \n"
"                           ��                                           ��                      \n"
"                       ��Ϊδ���                                  admin��ʱ���                \n\n" HIW
"************************************************************************************************\n\n" NOR);

    write(HIY "����λ���μ������ļ� " HIR "help member" HIY " �е�" HIR "�������Ա��" HIY "�\n\n" NOR);
    write(HIY "���˽������Ϣ��μ������ļ� " HIR "help member" HIY " ����֮��ص������ļ���\n\n" NOR);
    write(HIM "                     �ʳ����� ������˭ | Y��H�׻�Ӣ��ʷ ��ʦ�� \n" NOR);
    write(HIW "---------------------------------------------------------------\n\n" NOR);
    return 1;
}