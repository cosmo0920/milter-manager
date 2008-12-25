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

#ifdef HAVE_CONFIG_H
#  include "../../config.h"
#endif /* HAVE_CONFIG_H */

#include "milter-option.h"
#include "milter-enum-types.h"

#define MILTER_OPTION_GET_PRIVATE(obj)                  \
    (G_TYPE_INSTANCE_GET_PRIVATE((obj),                 \
                                 MILTER_TYPE_OPTION,    \
                                 MilterOptionPrivate))

typedef struct _MilterOptionPrivate	MilterOptionPrivate;
struct _MilterOptionPrivate
{
    guint32 version;
    MilterActionFlags action;
    MilterStepFlags step;
};

enum
{
    PROP_0,
    PROP_VERSION,
    PROP_ACTION,
    PROP_STEP
};

G_DEFINE_TYPE(MilterOption, milter_option, G_TYPE_OBJECT);

static void dispose        (GObject         *object);
static void set_property   (GObject         *object,
                            guint            prop_id,
                            const GValue    *value,
                            GParamSpec      *pspec);
static void get_property   (GObject         *object,
                            guint            prop_id,
                            GValue          *value,
                            GParamSpec      *pspec);

static void
milter_option_class_init (MilterOptionClass *klass)
{
    GObjectClass *gobject_class;
    GParamSpec *spec;

    gobject_class = G_OBJECT_CLASS(klass);

    gobject_class->dispose      = dispose;
    gobject_class->set_property = set_property;
    gobject_class->get_property = get_property;

    spec = g_param_spec_uint("version",
                             "Version",
                             "The milter protocol version of the option",
                             0,
                             G_MAXUINT32,
                             0,
                             G_PARAM_READWRITE);
    g_object_class_install_property(gobject_class, PROP_VERSION, spec);

    spec = g_param_spec_flags("action",
                              "Action",
                              "The action of the option",
                              MILTER_TYPE_ACTION_FLAGS,
                              MILTER_ACTION_NONE,
                              G_PARAM_READWRITE);
    g_object_class_install_property(gobject_class, PROP_ACTION, spec);

    spec = g_param_spec_flags("step",
                              "Step",
                              "The step of the option",
                              MILTER_TYPE_STEP_FLAGS,
                              MILTER_STEP_NONE,
                              G_PARAM_READWRITE);
    g_object_class_install_property(gobject_class, PROP_STEP, spec);

    g_type_class_add_private(gobject_class, sizeof(MilterOptionPrivate));
}

static void
milter_option_init (MilterOption *option)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);

    priv->version = 6;
    priv->action = MILTER_ACTION_NONE;
    priv->step = MILTER_STEP_NONE;
}

static void
dispose (GObject *object)
{
    G_OBJECT_CLASS(milter_option_parent_class)->dispose(object);
}

static void
set_property (GObject      *object,
              guint         prop_id,
              const GValue *value,
              GParamSpec   *pspec)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(object);
    switch (prop_id) {
      case PROP_VERSION:
        priv->version = g_value_get_uint(value);
        break;
      case PROP_ACTION:
        priv->action = g_value_get_flags(value);
        break;
      case PROP_STEP:
        priv->step = g_value_get_flags(value);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

static void
get_property (GObject    *object,
              guint       prop_id,
              GValue     *value,
              GParamSpec *pspec)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(object);
    switch (prop_id) {
      case PROP_VERSION:
        g_value_set_uint(value, priv->version);
        break;
      case PROP_ACTION:
        g_value_set_flags(value, priv->action);
        break;
      case PROP_STEP:
        g_value_set_flags(value, priv->step);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

MilterOption *
milter_option_new (guint32 version, MilterActionFlags action,
                   MilterStepFlags step)
{
    return g_object_new(MILTER_TYPE_OPTION,
                        "version", version,
                        "action", action,
                        "step", step,
                        NULL);
}

MilterOption *
milter_option_new_empty (void)
{
    return g_object_new(MILTER_TYPE_OPTION, NULL);
}

MilterOption *
milter_option_copy (MilterOption *option)
{
    return g_object_new(MILTER_TYPE_OPTION,
                        "version", milter_option_get_version(option),
                        "action", milter_option_get_action(option),
                        "step", milter_option_get_step(option),
                        NULL);
}

gboolean
milter_option_equal (MilterOption *option1, MilterOption *option2)
{
    MilterOptionPrivate *priv1, *priv2;

    priv1 = MILTER_OPTION_GET_PRIVATE(option1);
    priv2 = MILTER_OPTION_GET_PRIVATE(option2);

    return priv1->version == priv2->version &&
        priv1->action == priv2->action &&
        priv1->step == priv2->step;
}

guint32
milter_option_get_version (MilterOption *option)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    return priv->version;
}

void
milter_option_set_version (MilterOption *option, guint32 version)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    priv->version = version;
}

MilterActionFlags
milter_option_get_action (MilterOption *option)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    return priv->action;
}

void
milter_option_set_action (MilterOption *option, MilterActionFlags action)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    priv->action = action;
}

void
milter_option_add_action (MilterOption *option, MilterActionFlags action)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    priv->action |= action;
}

void
milter_option_remove_action (MilterOption *option, MilterActionFlags action)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    priv->action &= ~action;
}

MilterStepFlags
milter_option_get_step (MilterOption *option)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    return priv->step;
}

void
milter_option_set_step (MilterOption *option, MilterStepFlags step)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    priv->step = step;
}

void
milter_option_add_step (MilterOption *option, MilterStepFlags step)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    priv->step |= step;
}

void
milter_option_remove_step (MilterOption *option, MilterStepFlags step)
{
    MilterOptionPrivate *priv;

    priv = MILTER_OPTION_GET_PRIVATE(option);
    priv->step &= ~step;
}

gboolean
milter_option_combine (MilterOption *dest, MilterOption *src)
{
    MilterOptionPrivate *priv;

    if (milter_option_get_version(dest) !=
        milter_option_get_version(src))
        return FALSE;

    priv = MILTER_OPTION_GET_PRIVATE(dest);

    priv->step &= milter_option_get_step(src);
    priv->action &= milter_option_get_action(src);

    return TRUE;
}

gboolean
milter_option_merge (MilterOption *dest, MilterOption *src)
{
    MilterOptionPrivate *priv;

    if (milter_option_get_version(dest) !=
        milter_option_get_version(src))
        return FALSE;

    priv = MILTER_OPTION_GET_PRIVATE(dest);

    priv->step = milter_step_flags_merge(priv->step,
                                         milter_option_get_step(src));
    priv->action |= milter_option_get_action(src);

    return TRUE;
}

#define MILTER_NO_STEP_FLAGS                    \
    (MILTER_STEP_NO_CONNECT |                   \
     MILTER_STEP_NO_HELO |                      \
     MILTER_STEP_NO_ENVELOPE_FROM |             \
     MILTER_STEP_NO_ENVELOPE_RECIPIENT |        \
     MILTER_STEP_NO_BODY |                      \
     MILTER_STEP_NO_HEADERS |                   \
     MILTER_STEP_NO_END_OF_HEADER |             \
     MILTER_STEP_NO_REPLY_HEADER |              \
     MILTER_STEP_NO_UNKNOWN |                   \
     MILTER_STEP_NO_DATA |                      \
     MILTER_STEP_NO_REPLY_CONNECT |             \
     MILTER_STEP_NO_REPLY_HELO |                \
     MILTER_STEP_NO_REPLY_ENVELOPE_FROM |       \
     MILTER_STEP_NO_REPLY_ENVELOPE_RECIPIENT |  \
     MILTER_STEP_NO_REPLY_DATA |                \
     MILTER_STEP_NO_REPLY_UNKNOWN |             \
     MILTER_STEP_NO_REPLY_END_OF_HEADER |       \
     MILTER_STEP_NO_REPLY_BODY)                 \

#define MILTER_NORMAL_STEP_FLAGS                \
    (MILTER_STEP_SKIP |                         \
     MILTER_STEP_ENVELOPE_RECIPIENT_REJECTED |  \
     MILTER_STEP_HEADER_LEAD_SPACE)

MilterStepFlags
milter_step_flags_merge (MilterStepFlags dest, MilterStepFlags src)
{
    MilterStepFlags dest_no_step_flags;
    MilterStepFlags dest_normal_step_flags;

    dest_no_step_flags = dest & MILTER_NO_STEP_FLAGS;
    dest_no_step_flags &= (src & MILTER_NO_STEP_FLAGS);

    dest_normal_step_flags = dest & MILTER_NORMAL_STEP_FLAGS;
    dest_normal_step_flags |= (src & MILTER_NORMAL_STEP_FLAGS);

    return dest_no_step_flags | dest_normal_step_flags;
}

/*
vi:ts=4:nowrap:ai:expandtab:sw=4
*/
