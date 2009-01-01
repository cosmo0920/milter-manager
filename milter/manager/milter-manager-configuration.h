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

#ifndef __MILTER_MANAGER_CONFIGURATION_H__
#define __MILTER_MANAGER_CONFIGURATION_H__

#include <glib-object.h>

#include <milter/manager/milter-manager-objects.h>
#include <milter/manager/milter-manager-child.h>
#include <milter/manager/milter-manager-egg.h>

G_BEGIN_DECLS

#define MILTER_MANAGER_CONFIGURATION_ERROR           (milter_manager_configuration_error_quark())

#define MILTER_TYPE_MANAGER_CONFIGURATION            (milter_manager_configuration_get_type())
#define MILTER_MANAGER_CONFIGURATION(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), MILTER_TYPE_MANAGER_CONFIGURATION, MilterManagerConfiguration))
#define MILTER_MANAGER_CONFIGURATION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass), MILTER_TYPE_MANAGER_CONFIGURATION, MilterManagerConfigurationClass))
#define MILTER_MANAGER_IS_CONFIGURATION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), MILTER_TYPE_MANAGER_CONFIGURATION))
#define MILTER_MANAGER_IS_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), MILTER_TYPE_MANAGER_CONFIGURATION))
#define MILTER_MANAGER_CONFIGURATION_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), MILTER_TYPE_MANAGER_CONFIGURATION, MilterManagerConfigurationClass))

typedef enum
{
    MILTER_MANAGER_CONFIGURATION_ERROR_NOT_IMPLEMENTED,
    MILTER_MANAGER_CONFIGURATION_ERROR_NOT_EXIST,
    MILTER_MANAGER_CONFIGURATION_ERROR_UNKNOWN,
    MILTER_MANAGER_CONFIGURATION_ERROR_SAVE
} MilterManagerConfigurationError;

typedef struct _MilterManagerConfigurationClass MilterManagerConfigurationClass;

struct _MilterManagerConfiguration
{
    GObject object;
};

struct _MilterManagerConfigurationClass
{
    GObjectClass parent_class;

    gboolean     (*load)          (MilterManagerConfiguration *configuration,
                                   const gchar                *file_name,
                                   GError                    **error);
    gboolean     (*load_custom)   (MilterManagerConfiguration *configuration,
                                   const gchar                *file_name,
                                   GError                    **error);
    void         (*to_xml)        (MilterManagerConfiguration *configuration,
                                   GString                    *xml,
                                   guint                       indent);
};

GQuark        milter_manager_configuration_error_quark (void);
GType         milter_manager_configuration_get_type    (void) G_GNUC_CONST;

void         _milter_manager_configuration_init        (void);
void         _milter_manager_configuration_quit        (void);


MilterManagerConfiguration *
              milter_manager_configuration_new         (const gchar *first_property,
                                                        ...);

void          milter_manager_configuration_append_load_path
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *path);
void          milter_manager_configuration_prepend_load_path
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *path);
void          milter_manager_configuration_clear_load_paths
                                     (MilterManagerConfiguration *configuration);
const GList  *milter_manager_configuration_get_load_paths
                                     (MilterManagerConfiguration *configuration);
gboolean      milter_manager_configuration_load
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *file_name,
                                      GError                    **error);
gboolean      milter_manager_configuration_load_if_exist
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *file_name,
                                      GError                    **error);
gboolean      milter_manager_configuration_load_custom
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *file_name,
                                      GError                    **error);
gboolean      milter_manager_configuration_load_custom_if_exist
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *file_name,
                                      GError                    **error);
void          milter_manager_configuration_reload
                                     (MilterManagerConfiguration *configuration);

gboolean      milter_manager_configuration_save_custom
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *content,
                                      gssize                      size,
                                      GError                    **error);

gboolean      milter_manager_configuration_is_privilege_mode
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_set_privilege_mode
                                     (MilterManagerConfiguration *configuration,
                                      gboolean                    mode);
const gchar  *milter_manager_configuration_get_control_connection_spec
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_set_control_connection_spec
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *spec);

const gchar  *milter_manager_configuration_get_manager_connection_spec
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_set_manager_connection_spec
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *spec);
const gchar  *milter_manager_configuration_get_effective_user
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_set_effective_user
                                     (MilterManagerConfiguration *configuration,
                                      const gchar                *user_name);
guint         milter_manager_configuration_get_unix_socket_mode
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_set_unix_socket_mode
                                     (MilterManagerConfiguration *configuration,
                                      guint                       mode);
gboolean      milter_manager_configuration_is_remove_unix_socket_on_close
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_set_remove_unix_socket_on_close
                                     (MilterManagerConfiguration *configuration,
                                      gboolean                    remove);

MilterStatus  milter_manager_configuration_get_fallback_status
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_set_fallback_status
                                     (MilterManagerConfiguration *configuration,
                                      MilterStatus                status);
void          milter_manager_configuration_add_egg
                                     (MilterManagerConfiguration *configuration,
                                      MilterManagerEgg *egg);
MilterManagerEgg *
              milter_manager_configuration_find_egg
                                     (MilterManagerConfiguration *configuration,
                                      const gchar *name);
const GList  *milter_manager_configuration_get_eggs
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_remove_egg
                                     (MilterManagerConfiguration *configuration,
                                      MilterManagerEgg *egg);
void          milter_manager_configuration_remove_egg_by_name
                                     (MilterManagerConfiguration *configuration,
                                      const gchar *name);
void          milter_manager_configuration_clear_eggs
                                     (MilterManagerConfiguration *configuration);
MilterManagerChildren *milter_manager_configuration_create_children
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_add_applicable_condition
                                     (MilterManagerConfiguration *configuration,
                                      MilterManagerApplicableCondition *condition);
MilterManagerApplicableCondition *
              milter_manager_configuration_find_applicable_condition
                                     (MilterManagerConfiguration *configuration,
                                      const gchar *name);
const GList  *milter_manager_configuration_get_applicable_conditions
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_remove_applicable_condition
                                     (MilterManagerConfiguration *configuration,
                                      MilterManagerApplicableCondition *condition);
void          milter_manager_configuration_remove_applicable_condition_by_name
                                     (MilterManagerConfiguration *configuration,
                                      const gchar *name);
void          milter_manager_configuration_clear_applicable_conditions
                                     (MilterManagerConfiguration *configuration);

void          milter_manager_configuration_clear
                                     (MilterManagerConfiguration *configuration);

gchar        *milter_manager_configuration_to_xml
                                     (MilterManagerConfiguration *configuration);
void          milter_manager_configuration_to_xml_string
                                     (MilterManagerConfiguration *configuration,
                                      GString *string,
                                      guint indent);

G_END_DECLS

#endif /* __MILTER_MANAGER_CONFIGURATION_H__ */

/*
vi:nowrap:ai:expandtab:sw=4
*/
