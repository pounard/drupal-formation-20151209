<p>
  <?php if ($is_premium): ?>
    <?php echo t("@name is premium", ['@name' => format_username($account)]); ?>
  <?php else: ?>
    <?php echo t("@name is not premium", ['@name' => format_username($account)]); ?>
  <?php endif; ?>
</p>