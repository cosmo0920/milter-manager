/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) 2008  Kouhei Sutou <kou@cozmixng.org>
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MILTER_OPTION_H__
#define __MILTER_OPTION_H__

#include <sys/types.h>
#include <sys/socket.h>

#include <glib-object.h>

G_BEGIN_DECLS

#define MILTER_TYPE_OPTION            (milter_option_get_type())
#define MILTER_OPTION(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), MILTER_TYPE_OPTION, MilterOption))
#define MILTER_OPTION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass), MILTER_TYPE_OPTION, MilterOptionClass))
#define MILTER_IS_OPTION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), MILTER_TYPE_OPTION))
#define MILTER_IS_OPTION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), MILTER_TYPE_OPTION))
#define MILTER_OPTION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), MILTER_TYPE_OPTION, MilterOptionClass))

typedef enum
{
    /* no flags */
    MILTER_ACTION_NONE =                         0 << 0,
    /* filter may add headers */
    MILTER_ACTION_ADD_HEADERS =                  0x00000001L,
    /* filter may replace body */
    MILTER_ACTION_CHANGE_BODY =                  0x00000002L,
    /* filter may add recipients */
    MILTER_ACTION_ADD_RCPT =                     0x00000004L,
    /* filter may delete recipients */
    MILTER_ACTION_DELETE_RCPT =                  0x00000008L,
    /* filter may change/delete headers */
    MILTER_ACTION_CHANGE_HEADERS =               0x00000010L,
    /* filter may quarantine envelope */
    MILTER_ACTION_QUARANTINE =                   0x00000020L,
    /* filter may change "from" (envelope sender) */
    MILTER_ACTION_CHANGE_FROM =                  0x00000040L,
    /* add recipients incl. args */
    MILTER_ACTION_ADD_RCPT_WITH_PARAMETERS =     0x00000080L,
    /* filter can send set of symbols (macros) that it wants */
    MILTER_ACTION_SET_SYMBOL_LIST =              0x00000100L
} MilterActionFlags;

typedef enum
{
    MILTER_STEP_NONE =                   0 << 0,
    /* MTA should not send connect info */
    MILTER_STEP_NO_CONNECT =             0x00000001L,
    /* MTA should not send HELO info */
    MILTER_STEP_NO_HELO =                0x00000002L,
    /* MTA should not send MAIL info */
    MILTER_STEP_NO_MAIL =                0x00000004L,
    /* MTA should not send RCPT info */
    MILTER_STEP_NO_RCPT =                0x00000008L,
    /* MTA should not send body */
    MILTER_STEP_NO_BODY =                0x00000010L,
    /* MTA should not send headers */
    MILTER_STEP_NO_HEADERS =             0x00000020L,
    /* MTA should not send end of header */
    MILTER_STEP_NO_END_OF_HEADER =       0x00000040L,
    /* No reply for headers */
    MILTER_STEP_NO_REPLY_HEADER =        0x00000080L,
    /* MTA should not send unknown commands */
    MILTER_STEP_NO_UNKNOWN =             0x00000100L,
    /* MTA should not send DATA */
    MILTER_STEP_NO_DATA =                0x00000200L,
    /* MTA understands SMFIS_SKIP */
    MILTER_STEP_SKIP =                   0x00000400L,
    /* MTA should also send rejected RCPTs */
    MILTER_STEP_RCPT_REJECTED =          0x00000800L,
    /* No reply for connect */
    MILTER_STEP_NO_REPLY_CONNECT =       0x00001000L,
    /* No reply for HELO */
    MILTER_STEP_NO_REPLY_HELO =          0x00002000L,
    /* No reply for MAIL */
    MILTER_STEP_NO_REPLY_MAIL =          0x00004000L,
    /* No reply for RCPT */
    MILTER_STEP_NO_REPLY_RCPT =          0x00008000L,
    /* No reply for DATA */
    MILTER_STEP_NO_REPLY_DATA =          0x00010000L,
    /* No reply for UNKNOWN */
    MILTER_STEP_NO_REPLY_UNKNOWN =       0x00020000L,
    /* No reply for end of header */
    MILTER_STEP_NO_REPLY_END_OF_HEADER = 0x00040000L,
    /* No reply for body chunk */
    MILTER_STEP_NO_REPLY_BODY =          0x00080000L,
    /* header value leading space */
    MILTER_STEP_HEADER_LEAD_SPACE =      0x00100000L
} MilterStepFlags;

typedef struct _MilterOption         MilterOption;
typedef struct _MilterOptionClass    MilterOptionClass;

struct _MilterOption
{
    GObject object;
};

struct _MilterOptionClass
{
    GObjectClass parent_class;
};

GType              milter_option_get_type          (void) G_GNUC_CONST;

MilterOption      *milter_option_new               (gint              version,
                                                    MilterActionFlags action,
                                                    MilterStepFlags   step);
MilterOption      *milter_option_new_empty         (void);

guint              milter_option_get_version       (MilterOption      *option);
void               milter_option_set_version       (MilterOption      *option,
                                                    guint              version);

MilterActionFlags  milter_option_get_action        (MilterOption      *option);
void               milter_option_set_action        (MilterOption      *option,
                                                    MilterActionFlags  action);
void               milter_option_add_action        (MilterOption      *option,
                                                    MilterActionFlags  action);
void               milter_option_remove_action     (MilterOption      *option,
                                                    MilterActionFlags  action);

MilterStepFlags    milter_option_get_step          (MilterOption      *option);
void               milter_option_set_step          (MilterOption      *option,
                                                    MilterStepFlags    step);
void               milter_option_add_step          (MilterOption      *option,
                                                    MilterStepFlags    step);
void               milter_option_remove_step       (MilterOption      *option,
                                                    MilterStepFlags    step);

G_END_DECLS

#endif /* __MILTER_OPTION_H__ */

/*
vi:ts=4:nowrap:ai:expandtab:sw=4
*/
