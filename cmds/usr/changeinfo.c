#include <ansi.h>

#define CH_ID (1 << 0)
#define CH_NAME (1 << 1)

#define DEFAULT CH_ID | CH_NAME
#define HELP "/cmds/usr/color"

inherit F_CLEAN_UP;

protected void change_prompt(object me, int flag);
protected void change_input(object me, int flag, string arg);

int main(object me, string arg)
{
    int flag;

#ifndef NO_FEE
    if (!me->is_vip())
        return notify_fail("�㲻�ǻ�Ա,��Ȩʹ�ø�ָ�\n");
#endif

    if (arg)
    {
        if (sscanf(arg, "%*s-i%*s", arg) == 2)
            flag |= CH_ID;
        if (sscanf(arg, "%*s-n%*s", arg) == 2)
            flag |= CH_NAME;
    }
    if (!flag)
        flag = DEFAULT;
    tell_object(me, "���������� [ENTER]��ȡ�������� '~q'��ɫ��Э�������� '~h'\n");
    tell_object(me, WHT "[" HIW "Change Information" NOR + WHT "]��������������������������������\n" NOR);
    change_prompt(me, flag);
    return 1;
}

protected void change_prompt(object me, int flag)
{
    if (flag & CH_ID)
    {
        tell_object(me, "\nID-[" + me->query("id") + "]\n");
        tell_object(me, "��������Ĳ�ɫӢ�Ĵ��ţ�");
        input_to((
                     : change_input, me, flag:),
                 2);
    }
    else if (flag & CH_NAME)
    {
        tell_object(me, "\nNAME-[" + me->query("name") + "]\n");
        tell_object(me, "��������Ĳ�ɫ�������ƣ�");
        input_to((
                     : change_input, me, flag:),
                 2);
    }

    return;
}

protected void change_input(object me, int flag, string arg)
{
    string *res;
    string text;

    text = arg;
    arg = filter_color(arg);

    if (arg && me->query_temp("big5"))
        text = LANGUAGE_D->Big52GB(text);

    if (!arg)
        arg = "";

    if (arg == "~q")
    {
        tell_object(me, "ȡ�����롣\n");
        return;
    }
    if (arg == "~h")
    {
        HELP->main(me);
        return change_prompt(me, flag);
    }
    if (flag & CH_ID)
    {
        if (arg == "")
            tell_object(me, "������ɫӢ�Ĵ����趨��\n");
        else
        {
            if (!(res = me->set_idname(text, 0)))
            {
                tell_object(me, "���趨��Ӣ�Ĵ�����ԭ��Ӣ�Ĵ��Ų�ͬ���������趨��\n");
                return change_prompt(me, flag);
            }
            tell_object(me, "��ɫӢ�Ĵ��� '" + res[0] + "' �趨��ɡ�\n");
        }
        flag ^= CH_ID;
    }
    else if (flag & CH_NAME)
    {
        int len;

        if (arg == "")
            tell_object(me, "������ɫ���������趨��\n");
        else
        {
            arg = filter_color(trans_color(text, 3), 1);
            len = strlen(arg);
            if (len > 10 || len < 2)
            {
                tell_object(me, "�������Ʊ����� 1 �� 5 ��������֮�䣬�������趨��\n");
                return change_prompt(me, flag);
            }
            if (!is_chinese(filter_color(arg)))
            {
                tell_object(me, "��ʹ�á����ġ�ȡ���֣��������趨��\n");
                return change_prompt(me, flag);
            }

            if (!(res = me->set_idname(0, text)))
            {
                tell_object(me, "���趨������������ԭ���������Ʋ�ͬ���������趨��\n");
                return change_prompt(me, flag);
            }
            tell_object(me, "��ɫ�������� '" + res[1] + "' �趨��ɡ�\n");
        }
        flag ^= CH_NAME;
    }

    if (flag)
        return change_prompt(me, flag);
    return;
}

int help()
{
    write(@HELP
����ʹ������Ѷ

��ָ�����������ʹ������Ѷ���£�

    - i �޸����Ӣ�Ĵ���ɫ��
    - n �޸�����������Ƽ�ɫ��

�粻�Ӳ������ʾȫ���޸�

ָ���ʽ: changeinfo[-i][-n]

���ָ��: finger, nick
HELP);
    return 1;
}
