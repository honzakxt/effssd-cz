Drupal.behaviors.ssd_modules = {
  attach: function (context, settings) {
    (function ($) {
      function mediaqueryresponse(mql){
        if (mql.matches) {
          $("#block-views-front-index-modules-block-block .view-grouping-header").show();
          $('.playlist-toc-link').click( function() {
            $("#playlist-controller .playlist-table", context).hide(100);
            $('#playlist-controller', context).removeClass('expanded', 100);
          });
        }
      }
      // Used this example: http://stackoverflow.com/questions/7968303/wrapping-a-series-of-elements-between-two-h2-tags-with-jquery
      $("div.node-article div.wrap-module-sections h2").each(function(){
        var $set = $(this).nextUntil("h2").addBack();
        $set.wrapAll('<section class="module-section"><div class="container"> </div></section>');
      });
      $("div.node-article div.wrap-module-sections div.field-name-body").each(function(){
        $(this).find("div.field-item p:first").nextUntil("section.module-section").addBack().wrapAll('<section class="module-section"><div class="container"> </div></section>');
      });
      // Set popover titles to data-title.  This allows for graceful js degradation.
      $(".glossify-link").attr("title", function() {
        return $(this).attr('data-title');
      });
      // Apply popover
      $(".glossify-link").popover();
      // Show the feedback form.
      $(".feedback-link").mouseup(function (e) {
        if (e.which != 1) return false;
        $("#feedback-form", context).slideToggle();
      });
      // Hide Controller Table on click outside of controller
      $(document, context).mouseup(function (e) {
        if (e.which != 1) return false;
        // Make sure a click wasn't within one of these containers.
        var playlistController = $("#playlist-controller", context);
        var feedbackButton = $("#feedback-button", context);
        var feedbackForm = $("#block-feedback-form", context);
        if (!playlistController.is(e.target) && playlistController.has(e.target).length === 0) {
          if (!feedbackButton.is(e.target) && feedbackButton.has(e.target).length === 0) {
            if (!feedbackForm.is(e.target) && feedbackForm.has(e.target).length === 0) {
              $("#feedback-form", context).slideUp();
              $("#playlist-controller .playlist-table", context).hide(100);
              $('#playlist-controller', context).removeClass('expanded', 100);
            }
          }
        }
      });
      // Hide Controller on esc keypress
      $(document).keyup(function(e) {
        if (e.keyCode == 27) {
          $("#feedback-form", context).slideUp();
          $("#playlist-controller .playlist-table", context).hide(100);
          $('#playlist-controller', context).removeClass('expanded', 100);
        }
      });
      
      // Frontpage business.
      function hideAllCategoryChildren() {
        $(".view-front-index-modules-block").hide(); // @todo: target better
        $("#category-child-0").hide();
        $("#category-child-1").hide();
        $("#category-child-2").hide();
        $(".view-front-index-block .views-row .views-field-field-module-graphic img").css("background", "#789090");
        $(".view-front-index-block .views-row .views-field-description-field .field-content").css("color", "#000");
        $(".view-front-index-block .views-row .views-field-field-module-graphic img").css("opacity", ".5");
        $(".view-front-index-block .views-row .views-field-description-field .field-content").css("opacity", ".5");
        $(".view-front-index-block .views-row .views-field-name .field-content").css("opacity", ".5");
        $(".connect-bar").css("background", "#ddd");
      }
      function showCategoryChild(index) {
        hideAllCategoryChildren();
        $("#category-parent-" + index + " .views-field-field-module-graphic img").css("background", "#fff");
        $("#category-parent-" + index + " .views-field-description-field .field-content").css("color", "#fff");
        $("#category-parent-" + index + " .connect-bar").css("background", "#789090");
        $("#category-parent-" + index + " .views-field-field-module-graphic img").css("opacity", "1");
        $("#category-parent-" + index + " .views-field-description-field .field-content").css("opacity", "1");
        $("#category-parent-" + index + " .views-field-name .field-content").css("opacity", "1");
        $(".view-front-index-modules-block").show();
        $("#category-child-" + index).show();
      }
      $("#category-parent-0").hover(function() {
        showCategoryChild("0");
      });
      $("#category-parent-1").hover(function() {
        showCategoryChild("1");
      });
      $("#category-parent-2").hover(function() {
        showCategoryChild("2");
      });
      $("#block-views-front-index-modules-block-block .view-grouping-header").hide();
      hideAllCategoryChildren();
      // Mediaqueries for mobile:
      /**
       * IMPORTANT:
       * If this is changed, the breakpoint in mobile.scss
       * must be changed to match.
       */
      var mql = window.matchMedia("(max-width:767px)");
      // Runs only on page load.
      mediaqueryresponse(mql);
      if (mql.matches) {
        // @bug Doesn't run in Android/Firefox mobile - why?
        // On mobile front page, pre-select first icon.
        showCategoryChild("0");
      }
      // Runs constantly.
      mql.addListener(mediaqueryresponse);
    })(jQuery);
  }
}
