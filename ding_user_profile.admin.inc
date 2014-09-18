<?php
/**
 * @file
 * Admin routine logic.
 */

/**
 * Admin form structure.
 *
 * @param array $form
 *   The form, if any.
 * @param $form_state
 *   Form input statue, if any.
 *
 * @return array
 *   The form itself.
 */
function ding_user_profile_admin_form($form, $form_state) {
  $instances = field_info_instances('profile2', 'provider_alma');

  $form['user_profile_note'] = array(
    '#type' => 'item',
    '#markup' => t('The following fields will contain the description supplied below, however they might be hidden.'),
  );

  // These fields are standard in drupal.
  // The use edit form has fields which cannot be edited.
  $standard_fields = array(
    'pass' => array(
      'label' => 'pincode',
    ),
  );

  // Provider fields.
  foreach ($standard_fields + $instances  as $key => $instance) {
    if (isset($instances[$key]) && $instances[$key]['widget']['type'] == 'hidden') {
      continue;
    }

    $field = 'user_profile_' . $key;
    $form[$field] = array(
      '#type' => 'textarea',
      '#rows' => 2,
      '#title' => ucfirst($instance['label']),
      '#default_value' => t(variable_get($field, '')),
    );
  }

  return system_settings_form($form);
}
