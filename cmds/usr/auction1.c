// auction.c

#include <ansi.h>

#ifndef AUCTION_D
#define AUCTION_D       "/adm/daemons/auctiond"
#endif

inherit F_CLEAN_UP;

int help(object me);
int to_money(string str);

int main(object me, string arg)
{
        object ob;
        string name, str;
        int money;

        if (! arg) return help(me);

        if (arg == "cancel")
        {
                AUCTION_D->cancel_auction(me);
                return 1;
        }
        
        if (arg == "check")
        {
                if (stringp(str = AUCTION_D->check_auction_info()))
                {
                        write(str);
                        return 1;
                }
                return notify_fail("Ŀǰû���κζ�������������\n");
        }

        if (sscanf(arg, "%s for %s", name, str) == 2)
        {
                if (! objectp(ob = present(name, me)))
                        return notify_fail("������û�����������\n");

                ob->set_amount(1);

                if (! intp(money = to_money(str)) || money <= 0)
                        return notify_fail("����۸����\n");

                AUCTION_D->add_auction(me, ob, money);
                return 1;
        }

        if (sscanf(arg, "bid %s", str) == 1)
        {
                if (! intp(money = to_money(str)) || money <= 0)
                        return notify_fail("����۸����\n");

                if (me->query("balance") < money)
                        return notify_fail("��Ĵ��㡣\n");

                AUCTION_D->join_auction(me, money);
                return 1;
        }

        return help(me);
}

int to_money(string str)
{
        int money, gold, silver, coin;
        string type;

        if (sscanf(str, "%d gold %d silver %d coin",
                   gold, silver, coin) == 3)
                money = gold * 10000 + silver * 100 + coin;
                
        else if (sscanf(str, "%d gold %d silver",
                        gold, silver) == 2)
                money = gold * 10000 + silver * 100;

        else if (sscanf(str, "%d silver %d coin", 
                        silver, coin) == 2)
                money = silver * 100 + coin;

        else
        {
                if (sscanf(str, "%d %s", money, type) != 2)
                        return 0;

                switch (type)
                {
                case "gold": 
                        money *= 10000;
                        break;
                        
                case "silver":
                        money *= 100;
                        break;
                        
                case "coin":
                        break;
                        
                default: money = 0;
                }
        }
        return money;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : auction <��Ʒ> for <����> <Ǯ������>
           ������һ����Ʒ��

           auction bid <����> <Ǯ������>
           ����мۡ�
           
           auction check
           �쿴Ŀǰ����������������Ʒ��

           auction cancel
           ȡ���Լ�������Ʒ��������
           ȡ������ʱ�����������������������Ʒ�۸�֮�͵�
           ��ʮ��֮һ�ļ۸�����ΪΥԼ��Ӵ���п۳���

HELP
    );
        return 1;
}
